#ifndef TEMPSENSOR_H__
#define TEMPSENSOR_H__

#include "CommonTypes.h"
#include "IAgent.h"
#include "Location.h"
#include "Event.h"
#include "Thread.h"

namespace smartHouse {

class TempSensor : public IAgent
{
public:

	TempSensor(const string& name, const Location& location);
	~TempSensor();
	void Config(shared_ptr<IEnqueue> spEnq, shared_ptr<ISubscribe> spSub);
	void Run();
	bool GetIsActive() const;
	void SetDeactivate(bool flag);
	void Stop();

	//Task class
	class TempTask : public advcpp::IRunnable
	{
	public:
		TempTask(shared_ptr<IEnqueue> spEnq, const string& type, const string& payload, const Location& location)
		: m_spEnq(spEnq)
		, m_type(type)
		, m_payload(payload)
		, m_location(location)
		{
			m_continue = true;
		}

		virtual ~TempTask()
		{
			std::cout << "Exit Temp Task." << std::endl;
		}
			
		//override the 'Run' function in IRunnable
		virtual void Run()
		{
			while(m_continue)
			{
				shared_ptr<Event> spEvent(new Event(std::time(0), m_type, m_payload, m_location));
				if(!spEvent)
				{
					std::cerr << "temp spEvent is NULL." << std::endl;
					assert(false and "temp spEvent is NULL.");
				}
				m_spEnq->Enqueue(spEvent);
				std::cout << "TempSensor>> Enqueue" << std::endl;
				sleep(5);
			}
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
	shared_ptr<TempTask> spTask;
	bool m_isDeactivate;
};

}
#endif
