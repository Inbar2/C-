#ifndef THREAD_H__
#define THREAD_H__

#include <pthread.h>	//thread
#include <unistd.h>		//sleep
#include <sys/sysinfo.h>

#include "CommonTypes.h"
//#define NDEBUG 
#include <cassert>		//assert
#include "IRunnable.h"
#include "NonCopyable.h"
#include "ThreadException.h"

namespace advcpp {

class Thread : NonCopyable
{
public:

	Thread(shared_ptr<IRunnable> RunSPtr) /*throw(CreateThreadFailureException, InvArgThreadException)*/ /*comment the exception because of a warning while compiling: "dynamic exception specifications are deprecated in C++11 [-Wdeprecated]
"*/;
	~Thread() NOEXCEPT;
	void Join() NOEXCEPT;
	void Detach() NOEXCEPT;
	static void Sleep(unsigned int sec) NOEXCEPT;
	static void Yield() NOEXCEPT;
	static int CPU_Cores(); //TODO
	

private:
	static void* Work(void* ptr) NOEXCEPT;
	pthread_t m_tid;
	shared_ptr<IRunnable> m_spRunnable;
	bool m_isJoinNeeded;
	bool m_isDetachNeeded;
};

}
	
#endif
