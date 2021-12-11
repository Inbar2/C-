#ifndef SMARTHOUSEAPP_H__
#define SMARTHOUSEAPP_H__

#include <vector>
#include <memory> //shared_ptr reset
#include "Thread.h"
#include "CommonTypes.h"
#include "ConfigReader.h"
#include "EventsQueue.h"
#include "SubRegistry.h"
#include "AgentRecord.h"
#include "AgentFactory.h"

#include "EventPub.h"
#include "SubRegistry.h"
#include "SerialPub.h"
#include "EventDisp.h"

namespace smartHouse {


class SmartHouseApp : advcpp::NonCopyable
{
public:
	~SmartHouseApp();
	void Init(const string& configFile) throw(OpenFileFailedException);
	void Start() throw(LibraryIsMissingException);
	void Stop();
	
private:
	void CloseLibraries();
	
private:
	shared_ptr<ConfigReader> m_configReader;
	shared_ptr<EventsQueue> m_spEventsQ;
	shared_ptr<SubRegistry> m_spSubReg;
	std::vector<shared_ptr<IAgent> > m_agentsVec;
	std::vector<void*> m_handleLibVec;
	shared_ptr<EventDisp> m_spDispatcher;
	shared_ptr<advcpp::Thread> m_spThreadDisp;
	//LiveLogger m_liveLog;
};


}
#endif

/*
TODO still left to do:
*update the UML design with methods
*add live logger thread safe //https://coders-corner.net/2018/03/04/logger-class-in-c/
*add exception in signatures, and exception where needed, and asserts, cerr, remove std::cout where not really needed!
*arrange includes
*inline DTOR etc.
*stop app, stop threads "gracefully": ideas: signal stop => need to join and close all threads DTOR - stop 'while' runs
create DTOR in each agent that handle its thread and stop it
signal handler 
stop in IAgent function or Destroy func agents-can cause problem in destroy, so do stop and then destroy
*/



