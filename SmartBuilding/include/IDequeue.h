#ifndef IDEQUEUE_H__
#define IDEQUEUE_H__

#include "NonCopyable.h"

namespace smartHouse {

class Event;
class IDequeue : advcpp::NonCopyable
{
public:
	virtual ~IDequeue() {}
	virtual shared_ptr<Event> Dequeue() = 0;

private:

};

}
	
#endif
