#include "TempSensor.h"

//for task class
#include "CommonTypes.h"
#include "IRunnable.h"
#include "IEnqueue.h"
#include "Event.h"
using namespace smartHouse;

	
TempSensor::TempSensor(const string& name, const Location& location)
: m_name(name)
, m_location(location)
{
	m_isActive = false;
}

TempSensor::~TempSensor()
{
}

void TempSensor::Config(shared_ptr<IEnqueue> spEnq, shared_ptr<ISubscribe> spSub)
{
	m_spEnq = spEnq;
}

void TempSensor::Run()
{
	spTask.reset(new TempTask(m_spEnq, "AMBIENT_TEMP", "payload", m_location));
	if(!spTask)
	{
		//assert(false and "temp m_spTask is NULL.");
		std::cout << "temp spTask is NULL." << std::endl;
	}
	m_spThread = shared_ptr<advcpp::Thread>(new advcpp::Thread(spTask));
	m_isActive = true;
}

bool TempSensor::GetIsActive() const
{
	return m_isActive;
}

void TempSensor::SetDeactivate(bool flag)
{
}

void TempSensor::Stop()
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
		return new TempSensor(name, location);
	}
	
	void Deleter(IAgent* agent)
	{
		delete agent;
	}
}

