#include "SmartException.h"
using namespace smartHouse;

const char* OpenConfigFileFailedException::what()
{
	return "Exception: Can't open configuration file.";
}

const char* LibraryIsMissingException::what()
{
	return "Exception: Can't find so library.";
}

