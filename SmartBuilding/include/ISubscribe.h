#ifndef ISUBSCRIBE_H__
#define ISUBSCRIBE_H__

#include "CommonTypes.h"
#include "NonCopyable.h"

namespace smartHouse {

class EventCriteria;
class IEventHandler;
class ISubscribe : advcpp::NonCopyable
{
public:
	virtual ~ISubscribe() {}
	virtual void Add(const EventCriteria& ec, shared_ptr<IEventHandler> spHandler) = 0;
	virtual shared_ptr<IEventHandler> Remove(shared_ptr<IEventHandler> spHandler) = 0;

private:

};

}
	
#endif
