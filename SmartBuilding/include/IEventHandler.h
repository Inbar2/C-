#ifndef IEVENTHANDLER_H__
#define IEVENTHANDLER_H__

#include "CommonTypes.h"

namespace smartHouse {

class Event;
class IEventHandler
{
public:
	virtual ~IEventHandler() {};
	virtual void HandleEvent(shared_ptr<Event> spEvent) = 0;
	
private:
	
};

}
	
#endif
