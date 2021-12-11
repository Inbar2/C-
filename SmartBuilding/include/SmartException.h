#ifndef SMARTEXCEPTION_H
#define SMARTEXCEPTION_H

#include "CommonTypes.h"

namespace smartHouse
{
class OpenFileFailedException: public std::exception
{
	const char* what();
};

class LibraryIsMissingException: public std::exception
{
	const char* what();
};

}

#endif

