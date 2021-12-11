#include "SmokeSensor.h"

//for task class
#include "CommonTypes.h"
#include "IRunnable.h"
#include "IEnqueue.h"
#include "Event.h"
using namespace smartHouse;

	
SmokeSensor::SmokeSensor(const string& name, const Location& location)
: m_name(name)
, m_location(location)
{
	m_isActive = false;
}

SmokeSensor::~SmokeSensor()
{
}


void SmokeSensor::Config(shared_ptr<IEnqueue> spEnq, shared_ptr<ISubscribe> spSub)
{
	m_spEnq = spEnq;
}


void SmokeSensor::Run()
{
	spTask.reset(new SmokeTask(m_spEnq, "SMOKE_DETECT", "payload", m_location));
	if(!spTask)
	{
		//assert(false and "smoke spTask is NULL.");
		std::cout << "smoke spTask is NULL." << std::endl;
	}
	m_spThread = shared_ptr<advcpp::Thread>(new advcpp::Thread(spTask));
	m_isActive = true;
}

bool SmokeSensor::GetIsActive() const
{
	return m_isActive;
}

void SmokeSensor::SetDeactivate(bool flag)
{
}

void SmokeSensor::Stop()
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
		return new SmokeSensor(name, location);
	}
	
	void Deleter(IAgent* agent)
	{
		delete agent;
	}
}

