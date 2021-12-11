#include "ConfigReader.h"
using namespace smartHouse;


ConfigReader::ConfigReader()
{
}

ConfigReader::~ConfigReader()
{
}

std::vector<AgentRecord>& ConfigReader::GetRecordVec()
{
	return m_recordVec;
}
	
	
string ConfigReader::Trim(const string& str)
{
    size_t length = str.length();
    if(length == 0)
    {
        return str;
    }
    size_t begin = str.find_first_not_of(" \t\r\n\0;#");
    if(begin == std::string::npos)
    {
        begin = 0;
    }
    size_t end = str.find_last_not_of(" \t\r\n\0;#");
    if(end == std::string::npos)
    {
    	//there are no " \t\r\n\0;#" until the end of the line
        return str.substr(begin);
    }
    return str.substr(begin, end-begin+1);
}


string ConfigReader::ExtractKeyValue(const string& s, const string& key, bool* isKey)
{
    size_t startPos = s.find_first_not_of(" \t\r\n\0");
    size_t EndPos = s.find_first_of(" \t\r\n\0=", startPos);

    if(!(startPos == std::string::npos && EndPos == std::string::npos))
    {
	    string str = s;
    	string newS = str.substr(startPos, EndPos);
	    if(key == newS)
	    {
    		*isKey = true;
    	}
    }
    
	size_t pos = s.find('=');
	//check for empty line or with key that isn't a type
	if(pos == std::string::npos || Trim(s.substr(0, pos)) != key)
	{
		return "\0";
	}

	//check for empty value and return space char
	pos = s.find_first_not_of(" \t\n\r\0;#", pos+1);
	if(pos == std::string::npos)
	{
		return "\0";
	}
	
    return s.substr(pos);
}

void ConfigReader::ReadConfigFile(const string& fileName)
{
	string keys[] = {"type", "room", "floor", "log", "config"};
	std::vector<string> m_valuesVec;
	string line;
	string id;
	bool isIdFound = false;
	bool isKey = false;

	std::ifstream file(fileName.c_str());
	if(!file)
	{
		throw OpenFileFailedException();
	}

	string value;
	size_t i=0; //key index
	while(std::getline(file, line))
	{
		line = Trim(line);
		size_t length = 0;
		length = line.length();

		if((line[0] == '[') && (line[length-1] == ']')) //way to find section name
		{
			//get the next section in file
			if(isIdFound) 
			{
				i=0;
				AgentRecord record(id, m_valuesVec[0], m_valuesVec[1], m_valuesVec[2], m_valuesVec[3], m_valuesVec[4]);
				m_recordVec.push_back(record);
				m_valuesVec.clear();
			}

			id = line.substr(1, length-2);
			isIdFound = true;
			continue;
		}
		isKey = false;
		value = ExtractKeyValue(Trim(line), keys[i], &isKey);
		if(value.length() > 0 || isKey)
		{
			++i;
			m_valuesVec.push_back(value);
		}
	}
	
	//TODO - FIX: NEED TO BE ABLE TO ALSO GET THE LAST SECTION, THINK OF A MORE ELEGANT WAY
	if(!m_valuesVec.empty())
	{
		AgentRecord record(id, m_valuesVec[0], m_valuesVec[1], m_valuesVec[2], m_valuesVec[3], m_valuesVec[4]);
		m_recordVec.push_back(record);
	}
	file.close();
}

