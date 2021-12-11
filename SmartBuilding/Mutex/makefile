TARGET= WaitQ #Name of a file(e.g. executable or object files).
CC= g++
INC_PATH= ../include2
TH_SRC= ../Thread/
CFLAGS= -g -ansi -pedantic -Wall -Werror -lpthread -std=c++03#Extra flags to give to the C compiler.
CPPFLAGS=$(addprefix -I,$(INC_PATH))
SRCS= unitTest.cpp Mutex.cpp CondVar.cpp $(TH_SRC)Thread.cpp
OBJS= unitTest.o Mutex.o CondVar.o Thread.o

.PHONY: all clean run

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(CPPFLAGS) -o $(TARGET)


Thread.o: $(TH_SRC)Thread.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $<
CondVar.o: CondVar.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $<
Mutex.o: Mutex.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $<
unitTest.o: unitTest.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $<

	
include depends

depends:$(SRCS)
	$(CC) -MM $(CFLAGS) $(CPPFLAGS) $^ > depends
	

clean:
	rm -f $(TARGET) $(OBJS) depends #Command to remove a file.

run:
	./$(TARGET)
	
