#include "AgentRecord.h"
using namespace smartHouse;

AgentRecord::AgentRecord()
{
}

AgentRecord::AgentRecord(const string& id, const string& type, const string& room, const string& floor, const string& log, const string& config)
: m_id(id)
, m_type(type)
, m_room(room)
, m_floor(floor)
, m_log(log)
, m_config(config)
{

}

AgentRecord::~AgentRecord()
{
}


const string& AgentRecord::GetId() const
{
	return m_id;
}

const string& AgentRecord::GetType() const
{
	return m_type;
}

const string& AgentRecord::GetRoom() const
{
	return m_room;
}

const string& AgentRecord::GetFloor() const
{
	return m_floor;
}

const string& AgentRecord::GetLog() const
{
	return m_log;
}

const string& AgentRecord::GetConfig() const
{
	return m_config;
}
	
