#include "EventPub.h"
using namespace smartHouse;

EventPub::EventPub(shared_ptr<IPubImp> spIPubImp, shared_ptr<ISubLookup> spSubLook)
: m_spIPubImp(spIPubImp)
, m_spLookup(spSubLook)
{
}

EventPub::~EventPub()
{
}

void EventPub::PublishEvent(shared_ptr<Event> spEvent)
{
	if(!spEvent)
	{
		assert(false and "EventPub: spEvent is NULL.");
	}
	std::set<shared_ptr<IEventHandler> > subSet;
	
	if(m_spLookup->Lookup(spEvent, &subSet))
	{
		m_spIPubImp->Publish(spEvent, subSet);
	}
	else
	{
		std::cout << "PublishEvent>> No controllers subscribed to the event:" << spEvent->GetType() << std::endl;
	}
}


