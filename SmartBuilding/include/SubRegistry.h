#ifndef SUBREGISTRY_H__
#define SUBREGISTRY_H__

#include <tr1/unordered_map>

#include "ISubLookup.h"
#include "ISubscribe.h"
#include "IEventHandler.h"
#include "EventCriteria.h"
#include "Event.h"

//SubRegistry is noncopyable

class EventCriteria;
namespace smartHouse {
using std::tr1::unordered_map;

class SubRegistry : public ISubscribe, public ISubLookup
{
public:
	typedef unordered_map<string, SubSet>::iterator Iter;
	typedef unordered_map<string, SubSet>::const_iterator CIter;
	typedef	SubSet::iterator IterSet;
	SubRegistry();
	~SubRegistry();
	bool Lookup(shared_ptr<Event> spEvent, SubSet* retSubSet);

	void Add(const EventCriteria& ec, shared_ptr<IEventHandler> spHandler);
	shared_ptr<IEventHandler> Remove(shared_ptr<IEventHandler> spHandler);
	
	
private:
	unordered_map<string, SubSet> m_subReg;

};

}
	
#endif
