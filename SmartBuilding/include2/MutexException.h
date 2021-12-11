#ifndef MUTEXEXCEPTION_H
#define MUTEXEXCEPTION_H

#include "CommonTypes.h"

namespace advcpp
{
class MutexCreateLackedResourcesException: public std::exception
{
	const char* what();
};

class MutexCreateInsufficientMemoryException: public std::exception
{
	const char* what();
};

class MutexBusyCreateFailureException: public std::exception
{
	const char* what();
};

class LockedMutexException: public std::exception
{
	const char* what();
};

class UnlockedMutexException: public std::exception
{
	const char* what();
};

}

#endif

