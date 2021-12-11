#include "Mutex.h"
using namespace advcpp;

Mutex::Mutex() throw(MutexCreateLackedResourcesException, MutexCreateInsufficientMemoryException, MutexBusyCreateFailureException)
{
	int res = pthread_mutex_init(&m_mutex, 0);
	if(res == EAGAIN)
	{	
		throw MutexCreateLackedResourcesException();
	}
	if(res == ENOMEM)
	{	
		throw MutexCreateInsufficientMemoryException();
	}
	if(res == EBUSY)
	{	
		throw MutexBusyCreateFailureException();
	}
}

Mutex::~Mutex() NOEXCEPT
{
	int res = pthread_mutex_destroy(&m_mutex);
	if(res == EBUSY)
	{
		assert(false and "DTOR mutex failed: The implementation has detected an attempt to destroy the object referenced by mutex while it is locked or referenced by another thread.");
	}
	
	if(res == EINVAL)
	{
		assert(false and "DTOR mutex failed: The value specified by mutex is invalid.");
	}
}

void Mutex::Lock() throw(LockedMutexException)
{
	int res = pthread_mutex_lock(&m_mutex);

	if(res == EBUSY)
	{
		throw LockedMutexException();
	}
	m_isLocked = true;
}

void Mutex::Unlock() throw(UnlockedMutexException)
{
	int res = pthread_mutex_unlock(&m_mutex);
	if(res == EBUSY)
	{
		throw UnlockedMutexException();
	}
	m_isLocked = false;
}

bool Mutex::IsLocked() const
{
	return m_isLocked;
}


