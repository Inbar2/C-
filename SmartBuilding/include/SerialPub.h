#ifndef SERIALPUB_H__
#define SERIALPUB_H__

#include "NonCopyable.h"
#include "IPubImp.h"

namespace smartHouse {

class Event;
class IEventHandler;
class SerialPub : public IPubImp
{
public:
	SerialPub();
	~SerialPub();
	void Publish(shared_ptr<Event> spEvent, std::set<shared_ptr<IEventHandler> > subSet/*, Iter begin, Iter end*/);

private:

};

}
#endif
