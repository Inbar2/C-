#include "Location.h"
using namespace smartHouse;

Location::Location()
{
}

Location::Location(const Floor& floor, const Room& room)
: m_floor(floor)
, m_room(room)
{

}

Location::~Location()
{
}

/*
Location::Location(const Location& location)
{
	m_floor = location.m_floor;
	m_room = location.m_room;
}


Location& Location::operator=(const Location& location)
{
	if(this != &location)
	{
		m_floor = location.m_floor;
		m_room = location.m_room;
	}
	return *this;
}
*/

const Floor& Location::GetFloor() const
{
	return m_floor;
}

const Room& Location::GetRoom() const
{
	return m_room;
}


