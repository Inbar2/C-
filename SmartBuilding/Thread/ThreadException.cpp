#include "ThreadException.h"
using namespace advcpp;

const char* InvArgThreadException::what()
{
	return "Invalid Argument Exception";
}

const char* CreateThreadFailureException::what()
{
	return "Insufficient resources to create another thread";
}


