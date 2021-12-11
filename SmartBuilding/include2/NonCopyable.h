#ifndef NONCOPYABLE_H__
#define NONCOPYABLE_H__


namespace advcpp {

//interface class
class NonCopyable
{
public:
	NonCopyable() {}
	~NonCopyable() {} // destractor is not virtual because classes derive it privately
	
private:
	NonCopyable(const NonCopyable& nc);
	NonCopyable& operator=(const NonCopyable& nc);
};

}
#endif
