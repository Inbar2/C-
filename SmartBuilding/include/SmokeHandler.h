#ifndef SMOKEHANDLER_H__
#define SMOKEHANDLER_H__

#include "CommonTypes.h"
#include "IEventHandler.h"
#include "Event.h"

namespace smartHouse {

class SmokeHandler : public IEventHandler
{
public:
	void HandleEvent(shared_ptr<Event> spEvent);
	
private:
	
};

}
#endif
