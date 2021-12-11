#ifndef CONDVAREXCEPTION_H
#define CONDVAREXCEPTION_H

#include "CommonTypes.h"

namespace advcpp
{
class CondVarCreateLackedResourcesException: public std::exception
{
	const char* what();
};

class CondVarCreateInsufficientMemoryException: public std::exception
{
	const char* what();
};

class CondVarCreateBusyException: public std::exception
{
	const char* what();
};

class CondVarWaitFailureException: public std::exception
{
	const char* what();
};

class CondValSignalException: public std::exception
{
	const char* what();
};

class CondValBroadcastException: public std::exception
{
	const char* what();
};

}

#endif

