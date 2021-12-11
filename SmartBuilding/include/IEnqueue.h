#ifndef IENQUEUE_H__
#define IENQUEUE_H__

#include "CommonTypes.h"
#include "NonCopyable.h"

namespace smartHouse {

class Event;
class IEnqueue : advcpp::NonCopyable
{
public:
	virtual ~IEnqueue() {}
	virtual void Enqueue(shared_ptr<Event> elementValue) = 0;

private:

};

}
	
#endif
