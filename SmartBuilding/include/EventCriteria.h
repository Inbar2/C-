#ifndef EVENTCRITERIA_H__
#define EVENTCRITERIA_H__

#include <vector>
#include <cmath>
#include "CommonTypes.h"
#include "Floor.h"
#include "Room.h"

namespace smartHouse {

class EventCriteria
{
public:
	EventCriteria(const string& type, const Floor& floor, const Room& room);
	~EventCriteria();
	const string& GetCriType() const;
	const Floor& GetCriFloor() const;
	const Room& GetCriRoom() const;	
	string CreateKey() const;
	std::vector<string> CreateCriteriaContainer(const string& key);
	std::vector<string> GetKeyCombin(std::vector<string> keyCritVec);

	//bool operator==(const EventCriteria& other) const;
	
		
private:
	string m_type;
	Floor m_floor;
	Room m_room;
};

}
	
#endif
