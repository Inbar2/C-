#include "SerialPub.h"
using namespace smartHouse;


SerialPub::SerialPub()
{
}


SerialPub::~SerialPub()
{
}

void SerialPub::Publish(shared_ptr<Event> spEvent, std::set<shared_ptr<IEventHandler> > subSet)
{
	if(!spEvent)
	{
		assert(false and "SerialPub: spEvent is NULL.");
	}
	
	//go over each item in the set and run function - TODO change to FOREACH function
	for(itrSubSet it = subSet.begin(); it != subSet.end(); ++it)
	{
		(*it)->HandleEvent(spEvent);
	}
}

	
