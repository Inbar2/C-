#ifndef CONDVAR_H__
#define CONDVAR_H__

#include <pthread.h>	//thread
//#define NDEBUG 
#include <cassert>		//assert
#include "CommonTypes.h"
#include "NonCopyable.h"
#include "Mutex.h"
#include "CondVarException.h"

namespace advcpp {

class CondVar : private NonCopyable
{
public:
	CondVar() throw(CondVarCreateLackedResourcesException, CondVarCreateInsufficientMemoryException, CondVarCreateBusyException);
	~CondVar() NOEXCEPT;
	void Signal() throw(CondValSignalException); //will probably wake the last because of cash memory
	void Broadcast() throw(CondValBroadcastException);
	
	//T can be an object function(class) or function ptr
	template<class T>	
	void Wait(Mutex& mutex, const T& pred) throw(CondVarWaitFailureException); 

private:
	void InternalWait(Mutex& mutex) throw(CondVarWaitFailureException);
	
private:
	pthread_cond_t m_condVar;
};




template<typename T>	
void CondVar::Wait(Mutex& mutex, const T& pred) throw(CondVarWaitFailureException)
{
	while(pred())
	{
		InternalWait(mutex);
	}
}

}
	
#endif
