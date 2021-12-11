#include "mu_test.h"
#include "SmartHouseApp.h"


using namespace smartHouse;

//----------------------------------

UNIT(Test_Sensor_Collector)
	SmartHouseApp myApp;
	string file_name = "./config/configFile.ini";
	try
	{
		myApp.Init(file_name);
		myApp.Start();
	}
	catch(const std::exception& ex)
	{
	    std::cout << "Application failed to run: " << ex.what() << std::endl;

		//std::cerr << "Application failed to run." << dlerror() << std::endl;
		throw;
	}
	//let the app run for a while
	sleep(20);
	myApp.Stop();
END_UNIT


//----------------------------------

TEST_SUITE(CPP_Unit_Test_for_SmartHouse!)
	TEST(Test_Sensor_Collector)
	
END_SUITE
