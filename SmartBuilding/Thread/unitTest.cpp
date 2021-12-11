#include "mu_test.h"
#include "CommonTypes.h"
#include "IRunnable.h"
#include "Thread.h"
#include "Counter.h"
#include <vector>

using namespace advcpp;

//----------------------------------

UNIT(Test_Thread_Create_And_Join)	
	size_t num = 1000000;
	shared_ptr<Counter> countPtr(new Counter(num));
	try
	{
		Thread th(countPtr);
		th.Join();
	}
	catch(const std::exception& ex)
	{
		std::cerr << ex.what();
	}
	ASSERT_EQUAL_INT(countPtr->Result(), num);
END_UNIT

UNIT(Test_Thread_Create_And_Detach)	
	size_t num = 20000000;
	shared_ptr<Counter> countPtr(new Counter(num));
	try
	{
		Thread th(countPtr);
		
		th.Detach();
		th.Sleep(1);
	}
	catch(const std::exception& ex)
	{
		std::cerr << ex.what();
	}
	ASSERT_EQUAL_INT(countPtr->Result(), num);
END_UNIT

UNIT(Test_Thread_Create_And_Yield)	
	size_t num = 10000000;
	shared_ptr<Counter> countPtr(new Counter(num));
	try
	{
		Thread th(countPtr);
		th.Yield();
		th.Join();
	}
	catch(const std::exception& ex)
	{
		std::cerr << ex.what();
	}
	ASSERT_EQUAL_INT(countPtr->Result(), num);
END_UNIT

UNIT(Test_Thread_Create_And_Yield_Threads)	
	size_t num = 10000000;
	shared_ptr<Counter> countPtrA(new Counter(num));
	shared_ptr<Counter> countPtrB(new Counter(num));
	try
	{
		Thread th1(countPtrA);
		Thread th2(countPtrB);
		th1.Join();
		th1.Yield();
		th2.Join();
		
	}
	catch(const std::exception& ex)
	{
		std::cerr << ex.what();
	}
	ASSERT_EQUAL_INT(countPtrA->Result(), num);
	ASSERT_EQUAL_INT(countPtrB->Result(), num);
END_UNIT

UNIT(Test_Thread_Join_twice)	
	size_t num = 1000000;
	shared_ptr<Counter> countPtr(new Counter(num));
	try
	{
		Thread th(countPtr);
		th.Join();
		th.Join();
	}
	catch(const std::exception& ex)
	{
		std::cerr << ex.what();
	}
	ASSERT_EQUAL_INT(countPtr->Result(), num);
END_UNIT

UNIT(Test_Thread_Detach_twice)	
	size_t num = 1000000;
	shared_ptr<Counter> countPtr(new Counter(num));
	try
	{
		Thread th(countPtr);
		th.Detach();
		th.Detach();
		th.Sleep(1);
	}
	catch(const std::exception& ex)
	{
		std::cerr << ex.what();
	}
	ASSERT_EQUAL_INT(countPtr->Result(), num);
END_UNIT

UNIT(Test_Thread_Join_Detach)	
	size_t num = 1000000;
	shared_ptr<Counter> countPtr(new Counter(num));
	try
	{
		Thread th(countPtr);
		th.Join();
		th.Detach();
	}
	catch(const std::exception& ex)
	{
		std::cerr << ex.what();
	}
	ASSERT_EQUAL_INT(countPtr->Result(), num);
END_UNIT

UNIT(Test_Thread_Detach_Join)	
	size_t num = 1000000;
	shared_ptr<Counter> countPtr(new Counter(num));
	try
	{
		Thread th(countPtr);
		th.Detach();
		th.Sleep(1);
		th.Join();
	}
	catch(const std::exception& ex)
	{
		std::cerr << ex.what();
	}
	ASSERT_EQUAL_INT(countPtr->Result(), num);
END_UNIT

UNIT(Test_Create_2_Threads)
	size_t num = 100000000;
	shared_ptr<Counter> countPtrA(new Counter(num));
	shared_ptr<Counter> countPtrB(new Counter(num));
	try
	{
		Thread th1(countPtrA);
		Thread th2(countPtrB);
		th1.Join();
		th2.Join();
	}
	catch(const std::exception& ex)
	{
		std::cerr << ex.what();
	}
	ASSERT_EQUAL_INT(countPtrA->Result(), num);
	ASSERT_EQUAL_INT(countPtrB->Result(), num);
END_UNIT

UNIT(Test_Multi_Threads_Counter)
	std::vector<size_t> vec;

	size_t size = 0;
	for(int i=0; i<4; ++i)
	{
		size += 100000*(i+1);
		shared_ptr<Counter> countPtr(new Counter(100000*(i+1)));
		Thread tr(countPtr);
		tr.Join();
		vec.push_back(countPtr->Result());
	}
	size_t sum = 0;
	for(int i=0; i<4; ++i)
	{
		sum += vec[i];
	}
	ASSERT_EQUAL_INT(sum, size);
END_UNIT

UNIT(Test_CPU_Cores)
	size_t num = 100000000;
	shared_ptr<Counter> countPtr(new Counter(num));
	Thread th(countPtr);
	th.Join();
	th.CPU_Cores();

	ASSERT_EQUAL_INT(th.CPU_Cores(), sysconf(_SC_NPROCESSORS_ONLN));
END_UNIT


//----------------------------------

TEST_SUITE(CPP_Unit_Test_for_Threading!)
	TEST(Test_Thread_Create_And_Join)
	TEST(Test_Thread_Create_And_Detach)
	TEST(Test_Thread_Create_And_Yield)
	TEST(Test_Thread_Create_And_Yield_Threads)
	TEST(Test_Thread_Join_twice)
	TEST(Test_Thread_Detach_twice)
	TEST(Test_Thread_Join_Detach)
	TEST(Test_Thread_Detach_Join)
	TEST(Test_Create_2_Threads)
	TEST(Test_Multi_Threads_Counter)
	TEST(Test_CPU_Cores)
	
END_SUITE

