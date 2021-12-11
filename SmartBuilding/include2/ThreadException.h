#ifndef THREADEXCEPTION_H
#define THREADEXCEPTION_H

#include "CommonTypes.h"

namespace advcpp
{
	class InvArgThreadException: public std::exception
	{
		const char* what();

	};

	class CreateThreadFailureException: public std::exception
	{
		const char* what();

	};
}

#endif

/*Example

// exception constructor
#include <iostream>       // std::cout
#include <exception>      // std::exception

struct ooops : std::exception 
{
  const char* what() const noexcept 
  {
  	return "Ooops!\n";
  }
};

int main ()
{
  ooops e;
  std::exception* p = &e;
  
  try 
  {
      throw e;       // throwing copy-constructs: ooops(e)
  } 
  catch (std::exception& ex) 
  {
      std::cout << ex.what();
  }
  
  try 
  {
      throw *p;      // throwing copy-constructs: std::exception(*p)
  } 
  catch (std::exception& ex) 
  {
      std::cout << ex.what();
  }
  return 0;
}

result:
Ooops!
std::exception

*/
