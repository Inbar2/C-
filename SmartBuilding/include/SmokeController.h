#ifndef SMOKECONTROLLER_H__
#define SMOKECONTROLLER_H__

#include "CommonTypes.h"
#include "IAgent.h"
#include "SmokeHandler.h"
#include "EventCriteria.h"
#include "Location.h"

namespace smartHouse {

class SmokeController : public IAgent
{
public:
	SmokeController(const string& name, const Location& location);
	~SmokeController();
	void Config(shared_ptr<IEnqueue> spEnq, shared_ptr<ISubscribe> spSub);
	shared_ptr<SmokeHandler> GetSpSmokeHandler() const;
	void Run();
	bool GetIsActive() const;
	void SetDeactivate(bool flag);
	void Stop();
	
private:
	string m_name;
	Location m_location;
	shared_ptr<SmokeHandler> m_spHandler; //composition
	shared_ptr<ISubscribe> m_spSub;
	bool m_isActive;
	bool m_isDeactivate;
};

}

#endif
