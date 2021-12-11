#include "ConfigReader.h"
using namespace advcpp;

//~/work/advcpp/SmartBuild$ g++ -ansi -pedantic -Wall -Werror -std=c++03 -I./include -I../include ConfigReader.cpp AgentRecord.cpp ./test_and_data/reader_test.cpp 

int main()
{
	std::string fileName = "./config/configFile.ini";
	ConfigReader myConfigReader(fileName);
	myConfigReader.ReadFile();
	
	size_t vecSize = (myConfigReader.GetRecordVec()).size();

	std::cout << "num of agents: " << vecSize << std::endl;

	return 0;
}
