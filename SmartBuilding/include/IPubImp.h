#ifndef IPUBIMP_H__
#define IPUBIMP_H__

#include <set>
#include "NonCopyable.h"
#include "IEventHandler.h"

namespace smartHouse {

class Event;
class IPubImp : advcpp::NonCopyable
{
public:
	typedef std::set<shared_ptr<IEventHandler> >::iterator itrSubSet;
	virtual ~IPubImp() {}
	virtual void Publish(shared_ptr<Event> event, std::set<shared_ptr<IEventHandler> > subSet) = 0;

private:

};

}
	
#endif
