#include "EventCriteria.h"
using namespace smartHouse;

EventCriteria::EventCriteria(const string& type, const Floor& floor, const Room& room)
: m_type(type)
, m_floor(floor)
, m_room(room)
{
}

EventCriteria::~EventCriteria()
{
}

const string& EventCriteria::GetCriType() const
{
	return m_type;
}

const Floor& EventCriteria::GetCriFloor() const
{
	return m_floor;
}

const Room& EventCriteria::GetCriRoom() const
{
	return m_room;
}


string EventCriteria::CreateKey() const
{
	char delimeter = '|';
	return (m_type + delimeter + m_floor.Get() + delimeter + m_room.Get());
}

std::vector<string> EventCriteria::CreateCriteriaContainer(const string& key)
{
	//create from received key a vector with the possible criteria
	std::vector<string> critVec;
	size_t pos = 0;
	size_t fPos = 0;
	while (fPos < string::npos)
	{
		fPos = key.find_first_of("|", pos);
		string sub = key.substr(pos, fPos-pos);
		critVec.push_back(sub);
		pos = fPos+1;
	}
	return critVec;
}


//see file "combin_test" in folder for source modification
std::vector<string> EventCriteria::GetKeyCombin(std::vector<string> keyCritVec)
{
	const string wc = "WildCard";
	size_t numOfCrit = keyCritVec.size();
	std::vector<string> keyCombinVec;
	//create all criteria combinations
	for(size_t i=0; i<pow(2, numOfCrit); ++i)
	{
		string key;
		for(size_t j=0; j<numOfCrit; ++j) 
		{
			if (i & (1<<j )/*temp*/)
			{
				key += keyCritVec[j];
			}
			else
			{
				key+= wc; //any
			}
			if(j!=(numOfCrit-1))
			{
				key+='|';
			}
		}
		keyCombinVec.push_back(key);
	}
	return keyCombinVec;
}

//http://icarus.cs.weber.edu/~dab/cs1410/textbook/2.Core/bitops.html
//https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/
//https://www.cprogramming.com/tutorial/bitwise_operators.html
//https://www.geeksforgeeks.org/bitwise-algorithms/

/*
bool EventCriteria::operator==(const EventCriteria& other) const
{
	string wc = "WildCard";
	if((m_type == other.m_type && m_floor == other.m_floor && m_room == other.m_room)
	|| (m_type == other.m_type && m_floor == any && m_room == any)
	|| (m_type == any && m_floor == other.m_floor && m_room == any)
	|| (m_type == any && m_floor == any && m_room == other.m_room)
	|| (m_type == other.m_type && m_floor == other.m_floor && m_room == any)
	|| (m_type == other.m_type && m_floor == any && m_room == other.m_room)
	|| (m_type == any && m_floor == other.m_floor && m_room == other.m_room)	
	|| (m_type == any && m_floor == any && m_room == any))
	{
		return true;
	}
	return false;
}
*/

