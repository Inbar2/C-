#ifndef AGENTFACTORY_H__
#define AGENTFACTORY_H__

#include <dlfcn.h> //dl..open/error/sym/close need to Link with -ldl
#include "CommonTypes.h"
#include "NonCopyable.h"
#include "IAgent.h"
#include "Location.h"

//Without the -rdynamic (or something equivalent, like -Wl,--export-dynamic), symbols from the application itself will not be available for dynamic linking.

namespace smartHouse {

class AgentFactory : advcpp::NonCopyable
{
public:
	typedef IAgent* Create_t(const string& name, const Location& location);
	typedef void Destroy_t(IAgent*);
	
    //Load the library and map it in memory
    static void* DLOpenLib(const string& path);
    
    //Return a shared pointer on an instance of class loaded through a dynamic library
    static shared_ptr<IAgent> DLCreateInstance(void* handleLib, const string& name, const Location& location);
    
    //NOT NEEDED because in this project we work with shared ptr
    //delete a shared pointer on an instance of class loaded through a dynamic library
	static void DLDeleteInstance(void* handleLib, shared_ptr<IAgent> spInst);
    
    //Unload the library
    static void DLCloseLib(void* handleLib);
};

}

#endif
