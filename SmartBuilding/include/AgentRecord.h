#ifndef AGENTRECORD_H__
#define AGENTRECORD_H__

#include "CommonTypes.h"

namespace smartHouse {


class AgentRecord
{
public:
	AgentRecord();
	AgentRecord(const string& id, const string& type, const string& room, const string& floor, const string& log, const string& config);
	~AgentRecord();
	const string& GetId() const;
	const string& GetType() const;
	const string& GetRoom() const;
	const string& GetFloor() const;
	const string& GetLog() const;
	const string& GetConfig() const;
	

private:
	string m_id;
	string m_type;
	string m_room;
	string m_floor;
	string m_log;
	string m_config;
};


}
#endif
