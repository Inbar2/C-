#include "EventsQueue.h"
using namespace smartHouse;


EventsQueue::EventsQueue()
{
}

EventsQueue::~EventsQueue()
{
}

size_t EventsQueue::GetSize()
{
	return m_wq.Size();
}

bool EventsQueue::IsEmpty()
{
	return m_wq.IsEmpty();
}

void EventsQueue::Enqueue(shared_ptr<Event> elementValue)
{
	try
	{
		m_wq.Enqueue(elementValue);
	}
	catch(...)
	{
		throw;	
	}
}


shared_ptr<Event> EventsQueue::Dequeue()
{
	try
	{
		return m_wq.Dequeue();
	}
	catch(...)
	{
		throw;
	}
}
