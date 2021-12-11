#include "SubRegistry.h"
using namespace smartHouse;

SubRegistry::SubRegistry()
{
}

SubRegistry::~SubRegistry()
{
}


bool SubRegistry::Lookup(shared_ptr<Event> spEvent, SubSet* retSubSet)
{	
	if(!retSubSet)
	{
		assert(false and "SubRegistry: retSubSet is NULL.");
	}
	
	EventCriteria ec(spEvent->GetType(), spEvent->GetLocation().GetFloor(), spEvent->GetLocation().GetRoom());
	string key = ec.CreateKey();
	
	std::vector<string> eventCriVec = ec.CreateCriteriaContainer(key);
	std::vector<string> keyCombinVec = ec.GetKeyCombin(eventCriVec);

	typedef std::vector<string>::iterator VecIter;
	VecIter vItr;
			
	CIter cItr; /*typedef unordered_map<string, SubSet>::const_iterator*/
	for(vItr = keyCombinVec.begin(); vItr!=keyCombinVec.end(); ++vItr)
	{
		//std::cout << "SubRegistry>> combination: " << *vItr << std::endl;
		if((cItr = m_subReg.find(*vItr)) != m_subReg.end())
		{
			(*retSubSet).insert(cItr->second.begin(), cItr->second.end()); //is a set of shared_ptr<IEventHandler>
		}
	}
	
	if((*retSubSet).empty())
	{
		std::cout << "SubRegistry>> Finished Lookup: not found." << std::endl << std::endl;
		return false;
	}
	std::cout << "SubRegistry>> Finished Lookup: found." << std::endl << std::endl;
	return true;
}


void SubRegistry::Add(const EventCriteria& ec, shared_ptr<IEventHandler> spHandler)
{
	if(!spHandler)
	{
		assert(false and "SubRegistry: spHandler is NULL.");
	}
	
	//if key already exist insert spHandler to map, otherwise andd the key and insert.
	string key = ec.CreateKey();
	Iter itr;
	if((itr = m_subReg.find(key)) != m_subReg.end())
	{
		//insert Handler to set
		itr->second.insert(spHandler);
	}
	else
	{
		//key doesn't exist, add both key and Handler
		//Another option: m_subReg[ec].insert(spHandler);
		SubSet newSet;
		newSet.insert(spHandler);
		std::pair<string, SubSet> subPair(key, newSet);
		m_subReg.insert(subPair);	
	}
	
	//std::set<shared_ptr<IEventHandler> >::iterator setItr;
	//setItr = ((m_subReg.find(key))->second).find(spHandler);

	std::cout << "SubRegistry>> Add key: " <<  (m_subReg.find(key))->first << std::endl;
	std::cout << "SubRegistry>> Finished subscription." << std::endl << std::endl;
}


//remove Handler from map
shared_ptr<IEventHandler> SubRegistry::Remove(shared_ptr<IEventHandler> spHandler)
{
	if(!spHandler)
	{
		assert(false and "SubRegistry: spHandler is NULL.");
	}
	
	IterSet itrSet;
	for(Iter itr = m_subReg.begin(); itr != m_subReg.end(); ++itr)
	{
		if((itrSet = itr->second.find(spHandler)) != itr->second.end())
		{
			//found Handler
			shared_ptr<IEventHandler> removedCont(IEventHandler(*itrSet));
			if(itr->second.size()-1 == 0)
			{
				//if only the Handler to be removed is subscribed to the key, remove pair from the map.
				m_subReg.erase(itr);
			}
			else
			{
				//if there are other Handlers that are subscribed to the key, only remove the Handler from the set.
				itr->second.erase(itrSet);
			}
			std::cout << "SubRegistry>> Remove controller's handlers from subRegistry." << std::endl;
			break;
		}
	}

	std::cout << "SubRegistry>> Finished removing." << std::endl << std::endl;
	return *itrSet;
}
