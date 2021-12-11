#include "Event.h"
using namespace smartHouse;

Event::Event(const time_t& timestamp, const string& type, const string& payload, const Location& location)
: m_timestamp(timestamp)
, m_type(type)
, m_payload(payload)
, m_location(location)
{

}

Event::~Event()
{
}

const std::time_t& Event::GetTimestamp() const
{
	return m_timestamp;
}

const string& Event::GetType() const
{
	return m_type;
}

const Location& Event::GetLocation() const
{
	return m_location;
}

const string& Event::GetPayload() const
{
	return m_payload;
}

