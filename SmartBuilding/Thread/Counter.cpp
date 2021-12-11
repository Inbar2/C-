#include "Counter.h"
using namespace advcpp;

Counter::Counter(size_t size)
: m_size(size)
{
	m_count = 0;
}

Counter::~Counter()
{
}

void Counter::Run()
{
	 for(size_t i=0; i<m_size; ++i)
	 {
	 	++m_count;
	 }
}

int Counter::Result() const
{
	return m_count;
}

