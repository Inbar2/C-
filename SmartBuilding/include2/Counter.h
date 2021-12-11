#ifndef COUNTER_H__
#define COUNTER_H__

#include <stddef.h>		//size_t
#include "IRunnable.h"

namespace advcpp {

class Counter : public IRunnable
{
public:
	Counter(size_t size);
	~Counter();
	void Run();
	int Result() const;

private:
	size_t m_size;
	size_t m_count;
};

}
	
#endif
