#ifndef CARDSENSOR_H__
#define CARDSENSOR_H__

#include "CommonTypes.h"
#include "IAgent.h" //device is noncopyable
#include "Location.h"
#include "Event.h"
#include "Thread.h"

namespace smartHouse {

class CardSensor : public IAgent
{
public:
	CardSensor(const string& name, const Location& location);	
	~CardSensor();
	void Config(shared_ptr<IEnqueue> spEnq, shared_ptr<ISubscribe> spSub);
	void Run();
	bool GetIsActive() const;
	void SetDeactivate(bool flag);
	void Stop();
	//Task class
	class CardTask : public advcpp::IRunnable
	{
	public:
		CardTask(shared_ptr<IEnqueue> spEnq, const string& type, const string& payload, const Location& location)
		: m_spEnq(spEnq)
		, m_type(type)
		, m_payload(payload)
		, m_location(location)
		{
			m_continue = true;
		}

		virtual ~CardTask()
		{
			std::cout << "Exit Card Task." << std::endl;
		}

		//override the 'Run' function in IRunnable
		virtual void Run()
		{
			shared_ptr<Event> spEvent(new Event(std::time(0), m_type, m_payload, m_location));
			if(!spEvent)
			{
				std::cout << "card spEvent is NULL." << std::endl;
				assert(false and "card spEvent is NULL.");
			}
			m_spEnq->Enqueue(spEvent);
			std::cout << "CardSensor>> Enqueue" << std::endl;
		}
		
		virtual void SetContinue(bool flag)
		{
			m_continue = flag;
		}
		
		virtual bool GetIsContinue() const
		{
			return m_continue;
		}
		
	private:
		shared_ptr<IEnqueue> m_spEnq;
		string m_type;
		string m_payload;
		Location m_location;
		bool m_continue;
	};
	
private:
	string m_name;
	Location m_location;
	shared_ptr<IEnqueue> m_spEnq;
	shared_ptr<advcpp::Thread> m_spThread;
	bool m_isActive;
	shared_ptr<CardTask> spTask;
	bool m_isDeactivate;
};


}
#endif
