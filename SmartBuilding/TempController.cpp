#include "TempController.h"
using namespace smartHouse;

TempController::TempController(const string& name, const Location& location)
: m_name(name)
, m_location(location)
, m_spHandler(new TempHandler())
{
	m_isActive = false;
	m_isDeactivate = false;
}

TempController::~TempController()
{
	
}

void TempController::Config(shared_ptr<IEnqueue> spEnq, shared_ptr<ISubscribe> spSub)
{
	m_spSub = spSub;
	Run();
}

void TempController::Run()
{
	EventCriteria contEC("AMBIENT_TEMP", Floor("1"), Room("room_1_a"));
	m_spSub->Add(contEC, m_spHandler);
	m_isActive = true;
}

bool TempController::GetIsActive() const
{
	return m_isActive;
}

void TempController::SetDeactivate(bool flag)
{
	m_isDeactivate = flag;
}

shared_ptr<TempHandler> TempController::GetSpTempHandler() const
{
	return m_spHandler;
}

void TempController::Stop()
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
		return new TempController(name, location);
	}
	
	void Deleter(IAgent* agent)
	{
		delete agent;
	}
}
