#ifndef EVENT_H__
#define EVENT_H__

#include "CommonTypes.h"
#include "Location.h"
#include "NonCopyable.h"

namespace smartHouse {

class Event : private advcpp::NonCopyable
{
public:
	Event(const std::time_t& timestamp, const string& type, const string& payload, const Location& location);
	~Event();
	const std::time_t& GetTimestamp() const; //Current date/time based on current system

	const string& GetType() const;
	const Location& GetLocation() const;
	const string& GetPayload() const;
	

private:
	std::time_t m_timestamp;
	string m_type;
	string m_payload; //TODO add class
	Location m_location;
};

}
#endif
