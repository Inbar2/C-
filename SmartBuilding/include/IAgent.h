#ifndef IAGENT_H__
#define IAGENT_H__

#include "CommonTypes.h"
#include "ISubscribe.h"
#include "IEnqueue.h"
#include "WaitQueue.h"

namespace smartHouse {

class IAgent
{
public:
	virtual ~IAgent() {};
	virtual void Config(shared_ptr<IEnqueue> spEnq, shared_ptr<ISubscribe> spSub) = 0;
	virtual void Run() = 0;
	virtual bool GetIsActive() const = 0;
	virtual void SetDeactivate(bool flag) = 0;
	virtual void Stop() = 0;

private:

};

}
#endif
