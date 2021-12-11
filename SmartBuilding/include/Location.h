#ifndef LOCATION_H__
#define LOCATION_H__

#include "CommonTypes.h"
#include "Floor.h"
#include "Room.h"

namespace smartHouse {

class Location
{
public:
	Location();
	Location(const Floor& floor, const Room& room);
	~Location();
	
	//will be provided by compiler
	//Location(const Location& location);
	//Location& operator=(const Location& location);
	
	const Floor& GetFloor() const;
	const Room& GetRoom() const;
	

private:
	Floor m_floor;
	Room m_room;
};

}
#endif
