#include "Thread.h"
using namespace advcpp;

//sptr.get() function gets the regular ptr.

Thread::Thread(shared_ptr<IRunnable> RunSPtr) /*throw(CreateThreadFailureException, InvArgThreadException)*/ //pass shared_ptr by value = +1 to shared_ptr.
: m_spRunnable(RunSPtr)
, m_isJoinNeeded(true)
, m_isDetachNeeded(true)
{
	if(m_spRunnable == 0) //check if ptr is null
	{
		throw InvArgThreadException();
	}

	if(pthread_create(&m_tid, 0, &Work, &m_spRunnable) != 0)
	{
		throw CreateThreadFailureException();
	}
}

Thread::~Thread() NOEXCEPT
{
	//check that join/detach were done. if yes - no assert, otherwise do assert.
	if(m_isJoinNeeded && m_isDetachNeeded)
	{
		//std::cerr << "Error: Try to destroy thread without join/detach. Auto join." << std::endl;
		//Join();
		assert(false and "DTOR failed.");
	}
}

//reinterpret_cast converts any pointer type to any other pointer type, even of unrelated classes. The operation result is a simple binary copy of the value from one pointer to the other. All pointer conversions are allowed: neither the content pointed nor the pointer type itself is checked. It can also cast pointers to or from integer types.
void* Thread::Work(void* ptr) NOEXCEPT //ptr is the arg context in pthread_create, it will bring the context arg to the function Work.
{
	assert(ptr); //NULL check
	shared_ptr<IRunnable> runnablePtr = *reinterpret_cast<shared_ptr<IRunnable>* >(ptr); //this is a reinterpret cast of 
	try
	{
		runnablePtr->Run();
	}
	catch(const std::exception& ex)
	{
		std::cerr << ex.what();
		assert(false);
	}
	catch(...)
	{
		std::cerr << "Error: Unknown exception.";
		assert(false);
	}
	
	return 0;
}

void Thread::Join() NOEXCEPT
{
	if(m_isJoinNeeded && m_isDetachNeeded)
	{
		int res = 0;
		void** retVal = 0;
		if((res = pthread_join(m_tid, retVal)) == 0)
		{
			//join succeeded
			m_isJoinNeeded = false;
		}
		else
		{
			//if join thread more than once/other reasons
			std::cerr << "Error: Thread join failed.";
			assert(false and "Join failed.");
		}
	}
}

void Thread::Detach() NOEXCEPT
{
	if(m_isDetachNeeded && m_isJoinNeeded)
	{
		int res = 0;
		if((res = pthread_detach(m_tid)) == 0)
		{
			//detach succeeded
			m_isDetachNeeded = false;
		}
		else
		{
			//if detach thread more than once/other reasons
			std::cerr << "Error: Thread detach failed.";
			assert(false and "Detach failed.");
		}
	}
}

void Thread::Sleep(unsigned int sec) NOEXCEPT
{
	while(sec == sleep(sec));
}

//causes the calling thread to relinquish the CPU. The thread is placed at the end of the run queue for its static priority and another thread is scheduled to run.
void Thread::Yield() NOEXCEPT
{
	int res = 0;
	if((res = pthread_yield()) != 0)
	{
		std::cerr << "Error: Thread yield failed.";
		assert(false and "Yield failed.");
	}
}

int Thread::CPU_Cores()
{
	//return get_nprocs(); //processors available
	return get_nprocs_conf(); //processors configured
	//return sysconf(_SC_NPROCESSORS_ONLN);

}



