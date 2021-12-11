#ifndef TEMPHANDLER_H__
#define TEMPHANDLER_H__

#include "CommonTypes.h"
#include "IEventHandler.h"
#include "Event.h"

namespace smartHouse {

class TempHandler : public IEventHandler
{
public:
	void HandleEvent(shared_ptr<Event> spEvent);
	
private:
	
};

}
#endif
