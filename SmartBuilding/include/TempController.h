#ifndef TEMPCONTROLLER_H__
#define TEMPCONTROLLER_H__

#include "CommonTypes.h"
#include "IAgent.h"
#include "TempHandler.h"
#include "EventCriteria.h"
#include "Location.h"

namespace smartHouse {

class TempController : public IAgent
{
public:
	TempController(const string& name, const Location& location);
	~TempController();
	void Config(shared_ptr<IEnqueue> spEnq, shared_ptr<ISubscribe> spSub);
	shared_ptr<TempHandler> GetSpTempHandler() const;
	void Run();
	bool GetIsActive() const;
	void SetDeactivate(bool flag);	
	void Stop();
	
private:
	string m_name;
	Location m_location;
	shared_ptr<TempHandler> m_spHandler; //composition
	shared_ptr<ISubscribe> m_spSub;
	bool m_isActive;
	bool m_isDeactivate;
};

}

#endif
