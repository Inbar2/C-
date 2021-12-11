#include "CondVarException.h"
using namespace advcpp;

const char* CondVarCreateLackedResourcesException::what()
{
	return "The system lacked the necessary resources (other than memory) to initialize another condition variable.";
}

const char* CondVarCreateInsufficientMemoryException::what()
{
	return "Insufficient memory exists to initialize the condition variable.";
}

const char* CondVarCreateBusyException::what()
{
	return "The implementation has detected an attempt to reinitialize the object referenced by cond, a previously initialized, but not yet destroyed, condition variable.";
}

const char* CondVarWaitFailureException::what()
{
	return "Different mutexes were supplied the operation on the same condition variable.";
}

const char* CondValSignalException::what()
{
	return "The value cond does not refer to an initialized condition variable.";
}

const char* CondValBroadcastException::what()
{
	return "The value cond does not refer to an initialized condition variable.";
}

