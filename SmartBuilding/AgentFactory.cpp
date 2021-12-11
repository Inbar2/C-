#include "AgentFactory.h"
using namespace smartHouse;


void* AgentFactory::DLOpenLib(const string& path)
{
	void* handleLib = dlopen(path.c_str(), RTLD_LAZY);
    if(!handleLib)
    {
        std::cerr << "Can't open and load library: " << dlerror() << std::endl;
    }
    
    return handleLib;
}

//https://0x00sec.org/t/c-dynamic-loading-of-shared-objects-at-runtime/1498
shared_ptr<IAgent> AgentFactory::DLCreateInstance(void* handleLib, const string& name, const Location& location)
{
 	//variable is then casted to a function pointer
	Create_t* pCreateFunc = (Create_t*)(dlsym(handleLib, "Create"));
	if(!pCreateFunc)
	{
		DLCloseLib(handleLib);
		std::cerr << "Can't find allocator symbol in library: " << dlerror() << std::endl;
	}
 	
	shared_ptr<IAgent> spObj(pCreateFunc(name, location));
	return spObj;
}

void AgentFactory::DLDeleteInstance(void* handleLib, shared_ptr<IAgent> spInst)
{
 	//variable is then casted to a function pointer
	Destroy_t* deleteFunc = (Destroy_t*)(dlsym(handleLib, "Deleter"));
	if(!deleteFunc)
	{
		DLCloseLib(handleLib);
		std::cerr << "Can't find deleter symbol in library: " << dlerror() << std::endl;
	}
 
	deleteFunc(spInst.get());
}

void AgentFactory::DLCloseLib(void* handleLib)
{
	if(handleLib)
    {
        if(dlclose(handleLib) != 0)
    	{
			std::cerr << "Can't close library: " << dlerror() << std::endl;
		}
		std::cout << "Closed Library." << std::endl;
	}
}
