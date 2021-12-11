#include "CondVar.h"
using namespace advcpp;

CondVar::CondVar() throw(CondVarCreateLackedResourcesException, CondVarCreateInsufficientMemoryException, CondVarCreateBusyException)
{
	int res = pthread_cond_init(&m_condVar, 0);
	if(res == EAGAIN)
	{
		throw CondVarCreateLackedResourcesException();
	}
	
	if(res == ENOMEM)
	{
		throw CondVarCreateInsufficientMemoryException();
	}
	
	if(res == EBUSY)
	{
		throw CondVarCreateBusyException();
	}
}

CondVar::~CondVar() NOEXCEPT
{
	int res = pthread_cond_destroy(&m_condVar);
	if(res == EBUSY)
	{
		assert(false and "DTOR CondVar failed: The implementation has detected an attempt to destroy the object referenced by cond while it is referenced by another thread.");
	}
	
	if(res == EINVAL)
	{
		assert(false and "DTOR mutex failed: The value specified by cond is invalid.");
	}
}

//unblock at least one of the threads that are blocked on the specified condition variable cond (if any threads are blocked on cond).
void CondVar::Signal() throw(CondValSignalException)
{
	int res = pthread_cond_signal(&m_condVar);
	if(res == EINVAL)
	{
		throw CondValSignalException();
	}
}

//unblock all threads currently blocked on the specified condition variable cond.
void CondVar::Broadcast() throw(CondValBroadcastException)
{
	int res = pthread_cond_broadcast(&m_condVar);
	if(res == EINVAL)
	{
		throw CondValBroadcastException();
	}
}

void CondVar::InternalWait(Mutex& mutex) throw(CondVarWaitFailureException)
{
	int res = pthread_cond_wait(&m_condVar, &mutex.m_mutex);
	if(res == EINVAL)
	{
		throw CondVarWaitFailureException();
	}
}


