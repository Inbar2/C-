#include "EventDisp.h"
using namespace smartHouse;

EventDisp::EventDisp(shared_ptr<IDequeue> spIDeq, shared_ptr<EventPub> spEvePub)
: m_spIDeq(spIDeq)
, m_spEvePub(spEvePub)
{
	m_continue = true;
}

EventDisp::~EventDisp()
{
	std::cout << "Exit Dispatcher." << std::endl;
}

void EventDisp::Run()
{
	//always check for spEvent that comes from Dequeue
	while(m_continue)
	{
		try
		{
			shared_ptr<Event> spEvent = m_spIDeq->Dequeue();
			if(spEvent->GetType() == "STOP_DISP")
			{
				std::cout << "EventDisp>> Stop dispatcher." << std::endl;
				m_continue = false;
				break;
			}
			std::cout << "EventDisp>> Event type is: " << spEvent->GetType() << std::endl;
			m_spEvePub->PublishEvent(spEvent);
		}
		catch(std::exception& ex)
		{
			throw;
		}
	}
}

void EventDisp::SetIsContinue(bool flag)
{
	m_continue = flag;
}

