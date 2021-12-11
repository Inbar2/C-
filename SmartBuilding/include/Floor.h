#ifndef FLOOR_H
#define FLOOR_H

#include "CommonTypes.h"

namespace smartHouse
{

class Floor
{
public:
	Floor();
    Floor(const string& floor);
	//Floor(const Floor& floor);
	//Floor& operator=(const Floor& floor);
    const string& Get() const;

private:
    string m_floorName;
};




inline Floor::Floor()
{
}

inline Floor::Floor(const string& floor)
: m_floorName(floor)
{
}

inline const string& Floor::Get() const
{
    return m_floorName;
}

/*
inline Floor::Floor(const Floor& floor)
{
	m_floorName = floor.m_floorName;
}

inline Floor& Floor::operator=(const Floor& floor)
{
	if(this != &floor)
	{
		m_floorName = floor.m_floorName;
	}
	return *this;
}
*/

}
#endif
