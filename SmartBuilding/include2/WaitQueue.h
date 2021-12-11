#ifndef WAITQUEUE_H__
#define WAITQUEUE_H__

#include <queue>
#include "CommonTypes.h"
#include "Mutex.h"
#include "CondVar.h"

namespace advcpp {

template<typename T>
//TODO add container template Template <typename T, typename container=std::queue<T> >
class WaitQueue //No need to inherit from NonCopyable, because there is a non-copyable member in the class (mutex, condition).
{
public:
	// no need CTOR and DTOR, because compiler will do it for me to each member that already has CTOR
	bool IsEmpty();
	size_t Size();
	void Enqueue(const T& obj);
	T Dequeue();
	

private:
	 std::queue<T> m_queue;
	 Mutex m_mutexObj;
	 CondVar m_condVarObj;
};




//Can get regular queue or priority queue
//TODO add container template Template <typename T, typename container=std::queue<T> >
template<typename T>
class Predicate
{
public:
	Predicate(std::queue<T>& wq)
	: m_queue(wq)
	{
	}
	
	bool operator()() const
	{
		return m_queue.empty();
	}

private:
	std::queue<T>& m_queue;
};


#include "WaitQueue.hpp"

}
#endif

