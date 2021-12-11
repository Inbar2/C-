# makefile for parser exercise cpp

TARGET= smartHouse #Name of a file(e.g. executable or object files).
CC= g++
LIB_PATH= ./agentsLibs
INC_PATH= ./include
INC_Q_PATH= ./include2
SRC_MC_PATH= ./Mutex
SRC_TH_PATH= ./Thread
CFLAGS= -g -ansi -pedantic -Wall -Werror -lpthread -std=c++03#Extra flags to give to the compiler.
CPPFLAGSA=$(addprefix -I,$(INC_PATH))
CPPFLAGSB=$(addprefix -I,$(INC_Q_PATH))
LDFLAGS= -ldl -rdynamic #linking main program with the dlfcn code, and SO symbol access
SRCS= unitTest.cpp Event.cpp Location.cpp $(SRC_MC_PATH)/Mutex.cpp $(SRC_MC_PATH)/CondVar.cpp EventDisp.cpp EventPub.cpp SerialPub.cpp SubRegistry.cpp $(SRC_TH_PATH)/Thread.cpp EventCriteria.cpp SmartHouseApp.cpp ConfigReader.cpp EventsQueue.cpp AgentFactory.cpp AgentRecord.cpp
OBJS= unitTest.o Event.o Location.o Mutex.o CondVar.o EventDisp.o EventPub.o SerialPub.o SubRegistry.o Thread.o EventCriteria.o SmartHouseApp.o ConfigReader.o EventsQueue.o AgentFactory.o AgentRecord.o

.PHONY: all clean run

#compile with library - linking:
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(CPPFLAGSA) $(CPPFLAGSB) $(LDFLAGS) -o $(TARGET) -I$(LIB_PATH) -L $(LIB_PATH)
	export LD_LIBRARY_PATH=$(LIB_PATH)


Event.o: Event.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGSA) $(CPPFLAGSB) $<
Location.o: Location.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGSA) $(CPPFLAGSB) $<
Mutex.o: $(SRC_MC_PATH)/Mutex.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGSA) $(CPPFLAGSB) $<
CondVar.o: $(SRC_MC_PATH)/CondVar.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGSA) $(CPPFLAGSB) $<
EventDisp.o: EventDisp.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGSA) $(CPPFLAGSB) $<
EventPub.o: EventPub.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGSA) $(CPPFLAGSB) $<
SerialPub.o: SerialPub.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGSA) $(CPPFLAGSB) $<
SubRegistry.o: SubRegistry.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGSA) $(CPPFLAGSB) $<
EventCriteria.o: EventCriteria.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGSA) $(CPPFLAGSB) $<
Thread.o: $(SRC_TH_PATH)/Thread.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGSA) $(CPPFLAGSB) $<	
SmartHouseApp.o: SmartHouseApp.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGSA) $(CPPFLAGSB) $<	

ConfigReader.o: ConfigReader.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGSA) $(CPPFLAGSB) $<	
EventsQueue.o: EventsQueue.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGSA) $(CPPFLAGSB) $<
AgentFactory.o: AgentFactory.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGSA) $(CPPFLAGSB) $<	
AgentRecord.o: AgentRecord.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGSA) $(CPPFLAGSB) $<	


unitTest.o: unitTest.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGSA) $(CPPFLAGSB) $<

	
include depends

depends:$(SRCS)
	$(CC) -MM $(CFLAGS) $(CPPFLAGSA) $(CPPFLAGSB) $^ > depends
	

clean:
	rm -f $(TARGET) $(OBJS) depends #Command to remove a file.

run:
	@$(MAKE) && ./$(TARGET)
	
