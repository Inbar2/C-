#include "MutexException.h"
using namespace advcpp;

const char* MutexCreateLackedResourcesException::what()
{
	return "The system lacked the necessary resources (other than memory) to initialize another mutex.";
}

const char* MutexCreateInsufficientMemoryException::what()
{
	return "Insufficient memory exists to initialize the mutex.";
}

const char* MutexBusyCreateFailureException::what()
{
	return "The implementation has detected an attempt to reinitialize the object referenced by mutex, a previously initialized, but not yet destroyed, mutex.";
}

const char* LockedMutexException::what()
{
	return "mutex is currently locked";
}

const char* UnlockedMutexException::what()
{
	return "mutex is currently unlock";
}

