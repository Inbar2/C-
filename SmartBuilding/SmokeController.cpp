#include "SmokeController.h"
using namespace smartHouse;

SmokeController::SmokeController(const string& name, const Location& location)
: m_name(name)
, m_location(location)
, m_spHandler(new SmokeHandler())
{
	m_isActive = false;
	m_isDeactivate = false;
}

SmokeController::~SmokeController()
{

}

void SmokeController::Config(shared_ptr<IEnqueue> spEnq, shared_ptr<ISubscribe> spSub)
{
	m_spSub = spSub;
	Run();
}

void SmokeController::Run()
{
	EventCriteria contEC("SMOKE_DETECT", Floor("3"), Room("WildCard"));
	m_spSub->Add(contEC, m_spHandler);
	m_isActive = true;
}

bool SmokeController::GetIsActive() const
{
	return m_isActive;
}

void SmokeController::SetDeactivate(bool flag)
{
	m_isDeactivate = flag;
}

shared_ptr<SmokeHandler> SmokeController::GetSpSmokeHandler() const
{
	return m_spHandler;
}


void SmokeController::Stop()
{
	if(m_isDeactivate)
	{
		m_spSub->Remove(m_spHandler);
		m_isActive = false;
	}
}

//class factories
extern "C" 
{
	IAgent* Create(const string& name, const Location& location) 
	{
		return new SmokeController(name, location);
	}
	
	void Deleter(IAgent* agent)
	{
		delete agent;
	}
}
