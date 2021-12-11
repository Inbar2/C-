#ifndef EVENTPUB_H__
#define EVENTPUB_H__

#include "CommonTypes.h"
#include "IPubImp.h"
#include "ISubLookup.h"
#include "Event.h"
#include "EventCriteria.h"

namespace smartHouse {

class EventPub
{
public:
	EventPub(shared_ptr<IPubImp> spIPubImp, shared_ptr<ISubLookup> spSubLook);
	~EventPub();
	void PublishEvent(shared_ptr<Event> spEvent);


private:
	shared_ptr<IPubImp> m_spIPubImp;
	shared_ptr<ISubLookup> m_spLookup;

};

}
#endif
