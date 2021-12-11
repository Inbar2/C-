#include "CardSensor.h"

//for task class
#include "CommonTypes.h"
#include "IRunnable.h"
#include "IEnqueue.h"
#include "Event.h"
using namespace smartHouse;

	
CardSensor::CardSensor(const string& name, const Location& location)
: m_name(name)
, m_location(location)
{
	m_isActive = false;
}

CardSensor::~CardSensor()
{
}


void CardSensor::Config(shared_ptr<IEnqueue> spEnq, shared_ptr<ISubscribe> spSub)
{
	m_spEnq = spEnq;
}


void CardSensor::Run()
{
	spTask.reset(new CardTask(m_spEnq, "IDENTIFY_CARD", "payload", m_location));
	if(!spTask)
	{
		//assert(false and "card spTask is NULL.");
		std::cout << "card spTask is NULL." << std::endl;
	}
	m_spThread = shared_ptr<advcpp::Thread>(new advcpp::Thread(spTask));
	m_isActive = true;
}

bool CardSensor::GetIsActive() const
{
	return m_isActive;
}

void CardSensor::SetDeactivate(bool flag)
{
}

void CardSensor::Stop()
{
	if(m_isActive)
	{
		if(spTask->GetIsContinue())
		{
			spTask->SetContinue(false);
			spTask.reset();
			m_spThread->Join();
			m_spThread.reset();
			m_isActive = false;
		}
	}
}

//class factories
extern "C" 
{
	IAgent* Create(const string& name, const Location& location)  
	{
		return new CardSensor(name, location);
	}
	
	void Deleter(IAgent* agent)
	{
		delete agent;
	}
}

