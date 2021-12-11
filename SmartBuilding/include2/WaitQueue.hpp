#include "WaitQueue.h"
using namespace advcpp;


template<class T>
bool WaitQueue<T>::IsEmpty()
{
	m_mutexObj.Lock();
	bool res = m_queue.empty();
	m_mutexObj.Unlock();	

	return res;
}

template<class T>
size_t WaitQueue<T>::Size()
{
	m_mutexObj.Lock();
	size_t res = m_queue.size();
	m_mutexObj.Unlock();	
	
	return res;
}

template<class T>
void WaitQueue<T>::Enqueue(const T& obj)
{
	m_mutexObj.Lock();
	try
	{
		m_queue.push(obj);
	}
	catch(...)
	{
		m_mutexObj.Unlock();
		throw; //rethrow	
	}

	m_mutexObj.Unlock();
	m_condVarObj.Broadcast();
}

template<class T>
T WaitQueue<T>::Dequeue()
{
	m_mutexObj.Lock();

	m_condVarObj.Wait(m_mutexObj, Predicate<T>(m_queue)); //will run the internal wait function.

	T element;
	
	try
	{
		element = m_queue.front();
		m_queue.pop();
	}
	catch(...)
	{
		m_mutexObj.Unlock();
		throw;
	}
	
	m_mutexObj.Unlock();
	return element;
}

