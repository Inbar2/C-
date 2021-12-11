#ifndef EVENTSQUEUE_H__
#define EVENTSQUEUE_H__

#include "NonCopyable.h"
#include "IEnqueue.h"
#include "IDequeue.h"
#include "WaitQueue.h"

namespace smartHouse {


class EventsQueue : public IEnqueue, public IDequeue
{
public:
	EventsQueue();
	~EventsQueue();
	void Enqueue(shared_ptr<Event> elementValue);
	shared_ptr<Event> Dequeue();
	size_t GetSize(); 
	bool IsEmpty();
	
private:
	advcpp::WaitQueue<shared_ptr<Event> > m_wq; //has a waitable queue (composition)
};



}
#endif
