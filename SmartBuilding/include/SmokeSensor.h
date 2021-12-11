#ifndef SMOKESENSOR_H__
#define SMOKESENSOR_H__

#include "CommonTypes.h"
#include "IAgent.h" //device is noncopyable
#include "Location.h"
#include "Event.h"
#include "Thread.h"

namespace smartHouse {

class SmokeSensor : public IAgent
{
public:
	SmokeSensor(const string& name, const Location& location);	
	~SmokeSensor();
	void Config(shared_ptr<IEnqueue> spEnq, shared_ptr<ISubscribe> spSub);
	void Run();
	bool GetIsActive() const;
	void SetDeactivate(bool flag);
	void Stop();
	//Task class
	class SmokeTask : public advcpp::IRunnable
	{
	public:
		SmokeTask(shared_ptr<IEnqueue> spEnq, const string& type, const string& payload, const Location& location)
		: m_spEnq(spEnq)
		, m_type(type)
		, m_payload(payload)
		, m_location(location)
		{
			m_continue = true;
		}

		virtual ~SmokeTask()
		{
			std::cout << "Exit Smoke Task." << std::endl;
		}

		//override the 'Run' function in IRunnable
		virtual void Run()
		{
			shared_ptr<Event> spEvent(new Event(std::time(0), m_type, m_payload, m_location));
			if(!spEvent)
			{
				std::cout << "smoke spEvent is NULL." << std::endl;
				assert(false and "smoke spEvent is NULL.");
			}
			m_spEnq->Enqueue(spEvent);
			std::cout << "SmokeSensor>> Enqueue" << std::endl;
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
	shared_ptr<SmokeTask> spTask;
	bool m_isDeactivate;
};


}
#endif
