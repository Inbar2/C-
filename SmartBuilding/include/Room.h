#ifndef ROOM_H
#define ROOM_H

#include "CommonTypes.h"

namespace smartHouse
{

class Room
{
public:
	Room();
    Room(const string& room);
    //Room(const Room& room);
	//Room& operator=(const Room& room);
    const string& Get() const;

private:
    string m_roomName;
};




inline Room::Room()
{
}

inline Room::Room(const string& room)
: m_roomName(room)
{
}

inline const string& Room::Get() const
{
    return m_roomName;
}

/*
inline Room::Room(const Room& room)
{
	m_roomName = room.m_roomName;
}

inline Room& Room::operator=(const Room& room)
{
	if(this != &room)
	{
		m_roomName = room.m_roomName;
	}
	return *this;
}
*/

}
#endif
