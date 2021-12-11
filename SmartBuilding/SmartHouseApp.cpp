#include "SmartHouseApp.h"
using namespace smartHouse;

SmartHouseApp::~SmartHouseApp()
{
	//CloseLibraries();
	std::cout << "------ Exit SmartHouseApp ------" << std::endl;
}

void SmartHouseApp::Init(const string& configFile) throw(OpenFileFailedException)
{
	try
	{
		m_configReader.reset(new ConfigReader());
		try
		{
			m_configReader->ReadConfigFile(configFile);
		}
		catch(...)
		{
			throw;
		}
		m_spEventsQ.reset(new EventsQueue());
		m_spSubReg.reset(new SubRegistry());
		shared_ptr<SerialPub> spSerialPub(new SerialPub());
		shared_ptr<EventPub> spEvePub(new EventPub(spSerialPub, m_spSubReg));
		
		m_spDispatcher.reset(new EventDisp(m_spEventsQ, spEvePub));
	}
	catch(std::bad_alloc& ex)
	{
		std::cerr << "bad_alloc caught: " << ex.what() << std::endl;
		throw;
	}
}	

void SmartHouseApp::Start() throw(LibraryIsMissingException)
{	
	std::vector<AgentRecord> AgentRecordsVec;
	AgentRecordsVec = m_configReader->GetRecordVec();
	bool isSmokeSoOpen = false;
	bool isSprinklerSoOpen = false;
	bool isTempSoOpen = false;
	bool isHVACSoOpen = false;
	bool isCardSoOpen = false;	
	
	//Load configuration ini file
	void* handleLib;
	std::cout << "Reading configuration file:" << std::endl;
	//TODO: Fix - allow multiple instances from same library, change open and saving both agent and lib. Maybe move the path to the ini file.
	for(std::vector<AgentRecord>::iterator itr = AgentRecordsVec.begin(); itr != AgentRecordsVec.end(); ++itr)
	{
		string agentType = itr->GetType();

		if(agentType == "Smoke_detector" && !isSmokeSoOpen)
		{
			handleLib = AgentFactory::DLOpenLib("./agentsLibs/lib" + agentType + ".so");
			isSmokeSoOpen = true;
		}
		else if(agentType == "Sprinkler" && !isSprinklerSoOpen)
		{
			handleLib = AgentFactory::DLOpenLib("./agentsLibs/lib" + agentType + ".so");
			isSprinklerSoOpen = true;
		}
		else if(agentType == "Ambient_temp" && !isTempSoOpen)
		{
			handleLib = AgentFactory::DLOpenLib("./agentsLibs/lib" + agentType + ".so");
			isTempSoOpen = true;
		}
		else if(agentType == "HVAC" && !isHVACSoOpen)
		{
			handleLib = AgentFactory::DLOpenLib("./agentsLibs/lib" + agentType + ".so");
			isHVACSoOpen = true;
		}
		else if(agentType == "IDentCard" && !isCardSoOpen)
		{
			handleLib = AgentFactory::DLOpenLib("./agentsLibs/lib" + agentType + ".so");
		}/*
		else if(agentType == "ZigBeeLock")
		{
			handleLib = AgentFactory::DLOpenLib("./agentsLibs/lib" + agentType + ".so");
		}
		else if(agentType == "PhilipsHue")
		{
			handleLib = AgentFactory::DLOpenLib("./agentsLibs/lib" + agentType + ".so");
		}
		else if(agentType == "Noise_detector")
		{
			handleLib = AgentFactory::DLOpenLib("./agentsLibs/lib" + agentType + ".so");
		}*/
		else
		{
			string name = "lib" + agentType + ".so";
			std::cerr << "Can't create agent. There is No library named: " << name << std::endl;
			continue;
		}
		
		Location location(Floor(itr->GetFloor()), Room(itr->GetRoom()));
		shared_ptr<IAgent> spAgent = AgentFactory::DLCreateInstance(handleLib, itr->GetId(), location);
		std::cout << "Creating agent of type: " << agentType << std::endl;
		
		//save the agents that have been created
		m_agentsVec.push_back(spAgent);
				
				
		spAgent->Config(m_spEventsQ, m_spSubReg);
		
		//keep vector with libs handle and close them at the end of reading
		m_handleLibVec.push_back(handleLib);
		
	} //end reading config file

	//Activate sensors
	for(std::vector<shared_ptr<IAgent> >::iterator aItr = m_agentsVec.begin(); aItr!=m_agentsVec.end(); ++aItr)
	{
		if(!((*aItr)->GetIsActive()))
		{
			(*aItr)->Run();
		}
	}
	
	//Run dispatcher	
	m_spThreadDisp.reset(new advcpp::Thread(m_spDispatcher));
}

void SmartHouseApp::Stop()
{
	std::cout << "---SmartHouseApp>> Stop all " << m_agentsVec.size() << " agents---" << std::endl;
	//Need to stop sensors first and only after that the controllers - after: eventsQ is empty
	for(std::vector<shared_ptr<IAgent> >::iterator aItr = m_agentsVec.begin(); aItr!=m_agentsVec.end(); ++aItr)
	{
		(*aItr)->Stop();
	}
	
	while(!m_spEventsQ->IsEmpty());
	
	//stop controllers from handling events, all sensors are already isActive=false.
	for(std::vector<shared_ptr<IAgent> >::iterator aItr = m_agentsVec.begin(); aItr!=m_agentsVec.end(); ++aItr)
	{
		(*aItr)->SetDeactivate(true); //de-activate the controller
		(*aItr)->Stop();
	}
	
	m_spEventsQ->Enqueue(shared_ptr<Event>(new Event(std::time(0), "STOP_DISP", "", Location(Floor(""), Room("")))));
	m_spDispatcher.reset();
	m_spThreadDisp->Join(); //otherwise will get assert
}

void SmartHouseApp::CloseLibraries()
{
	//Close libraries
	for(std::vector<void*>::iterator hlItr = m_handleLibVec.begin(); hlItr!=m_handleLibVec.end(); ++hlItr)
	{
		AgentFactory::DLCloseLib(*hlItr);
	}
}


