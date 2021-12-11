#ifndef IRUNNABLE_H__
#define IRUNNABLE_H__

#include "NonCopyable.h"

namespace advcpp {

class IRunnable : NonCopyable
{
public:
	virtual ~IRunnable() {}
	virtual void Run() = 0;

private:

};

}
	
#endif
