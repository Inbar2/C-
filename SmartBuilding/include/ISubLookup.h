#ifndef ISUBLOOKUP_H__
#define ISUBLOOKUP_H__

#include <set>
#include "CommonTypes.h"
#include "NonCopyable.h"

namespace smartHouse {

class Event;
class IEventHandler;
class ISubLookup : advcpp::NonCopyable
{
public:
	typedef std::set<shared_ptr<IEventHandler> > SubSet;
	virtual ~ISubLookup() {}
	virtual bool Lookup(shared_ptr<Event> spEvent, SubSet* retSubSet) = 0;

private:

};

}
	
#endif
