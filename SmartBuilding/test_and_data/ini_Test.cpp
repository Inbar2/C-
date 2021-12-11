#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
//#include <set>
#include <tr1/memory>
#include <exception>
#include "SmartException.h"
using std::tr1::shared_ptr;
using std::string;

//g++ -ansi -pedantic -Wall -Werror -std=c++03 -I../include -I../../include ini_test.cpp

//use source and change it:
//https://www.experts-exchange.com/questions/27274326/How-to-read-INI-file-on-Linux-using-c.html

using namespace advcpp;

/*
bool errorreturn(const std::string & errorobject, const std::string & errormessage, std::ostream & errorstream)
{
    errorstream << ">>"<< errorobject << "<<, " << errormessage;
    return false;
}
*/

std::string trim(const std::string& s)
{
    size_t length = s.length();
    if(length == 0)
    {
        return s;
    }
    size_t b = s.find_first_not_of(" \t\r\n\0;#");
    if(b == std::string::npos)
    {
        b = 0;
    }
    size_t e = s.find_last_not_of(" \t\r\n\0;#");
    if(e == std::string::npos)
    {
        return s.substr(b);
    }
    return s.substr(b, e-b+1);
}

/*
std::string makelower(const string& s)
{
   string str = s;
    for(std::string::iterator itr=str.begin(); itr!=str.end(); ++itr)
        if(tolower(*itr) != (int)*itr)
        {
            *itr = (char)tolower(*itr);
        }
    return str;
}
*/

std::string value_for_key(const string& s, const string& k, bool* isKey)
{
    size_t startPos = s.find_first_not_of(" \t\r\n\0");
    size_t EndPos = s.find_first_of(" \t\r\n\0=", startPos);
	//std::cout << "keyS: " << startPos << std::endl;
	//std::cout << "keyE: " << EndPos << std::endl;
    if(!(startPos == std::string::npos && EndPos == std::string::npos))
    {
	    string str = s;
    	string newS = str.substr(startPos, EndPos);
		std::cout << "key: " << newS << std::endl;
	    if(k == newS)
	    {
    		*isKey = true;
    	}
    }
    
	size_t pos = s.find('=');
	//check for empty line or with key that isn't a type
	if(pos == std::string::npos || trim/*(makelower*/(s.substr(0,pos))/*)*/ != k)
	{
		std::cout << "////////////////////////////////////" << std::endl;
		return "\0";
	}

	//check for empty value and return space char
	pos = s.find_first_not_of(" \t\n\r\0;#", pos+1);
	if(pos == std::string::npos)
	{
		std::cout << "**********************************" << std::endl;
		return "\0";
	}
	
    return s.substr(pos);
}


void getini(const string& path, std::vector<string>& m_recordsVec/*, std::vector<*/)
{
    string keys[] = {"type", "room", "floor", "log", "config"};
    string s, k;
    string line;
    bool isSecFound = false;
    
    std::ifstream file(path.c_str());
    if(!file)
    {
   		throw OpenFileFailedException();
    }
    
    string value;
    size_t i=0; //key index
	while(std::getline(file, s))
	{
		s = trim(s);
		size_t length = 0;
		length = s.length();
		std::cout << "string: " << s << std::endl;
		std::cout << "length: " << length << std::endl;
		if((s[0] == '[') && (s[length-1] == ']')) //way to find section name
		{
			string id;
			string type;
			string room;
			string floor;
			string log;
			string config;
			//get the next section in file
			if(isSecFound) 
			{
				i=0;
				//m_recordsVec.push_back(record);
			}
			id = s.substr(1, length-2);
			std::cout << "section: " << id << std::endl;
			isSecFound = true;
			continue;
		}

		bool isKey = false;
		std::cout << "i-----------> " << i << std::endl;
		std::cout << trim(s) << std::endl;
		value = value_for_key(trim(s), keys[i], &isKey);
				std::cout << "return val for key: " << value << std::endl;
		if(value.length() > 0 || isKey)
		{
			++i;
			std::cout << "Value #" << i << ": " << value << std::endl;
		}
	}
      
  	file.close();
  	//delete [] keys;
	std::cout << "length: " << value.length() << std::endl;
    std::cout << "Value: " << value << std::endl;
}


int main()
{
	std::string fileName = "../config/configFile.ini";
	std::vector<string> m_recordsVec;
	//std::vector<AgentRecord> m_recordsVec;
	//read one config section at a time
	getini(fileName, m_recordsVec);

	return 0;
}
