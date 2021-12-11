#ifndef EVENTDISP_H__
#define EVENTDISP_H__

#include "CommonTypes.h"
#include "IRunnable.h"
#include "IDequeue.h"
#include "EventPub.h"
#include "Event.h"

namespace smartHouse {

class EventDisp : public advcpp::IRunnable
{
public:
	EventDisp(shared_ptr<IDequeue> spIDeq, shared_ptr<EventPub> spEvePub);
	~EventDisp();
	void Run();
	void SetIsContinue(bool flag);

private:
	shared_ptr<IDequeue> m_spIDeq;
	shared_ptr<EventPub> m_spEvePub;
	bool m_continue;
};

}
#endif
