#ifndef MUTEX_H__
#define MUTEX_H__

#include <pthread.h>	//thread
//#define NDEBUG 
#include <cassert>
#include "CommonTypes.h"
#include "NonCopyable.h"
#include "MutexException.h"

namespace advcpp {

class CondVar;
class Mutex : private NonCopyable
{
	friend class CondVar;

public:
	Mutex() throw(MutexCreateLackedResourcesException, MutexCreateInsufficientMemoryException, MutexBusyCreateFailureException);
	~Mutex() NOEXCEPT;
	void Lock() throw(LockedMutexException);
	void Unlock() throw(UnlockedMutexException);
	bool IsLocked() const;

private:
	pthread_mutex_t m_mutex;
	bool m_isLocked;
};

}

#endif
