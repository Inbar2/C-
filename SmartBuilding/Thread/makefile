# makefile for parser exercise cpp

TARGET= Threads #Name of a file(e.g. executable or object files).
CC= g++
INC_PATH= ../include2
CFLAGS= -g -ansi -pedantic -Wall -Werror -lpthread -std=c++03#Extra flags to give to the C compiler.
CPPFLAGS=$(addprefix -I,$(INC_PATH))
SRCS= unitTest.cpp Thread.cpp Counter.cpp
OBJS= unitTest.o Thread.o Counter.o

.PHONY: all clean run

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(CPPFLAGS) -o $(TARGET)


Thread.o: Thread.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $<
Counter.o: Counter.cpp
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
	
