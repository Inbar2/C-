# makefile for parser exercise cpp

TARGET= ParserEX #Name of a file(e.g. executable or object files).
CPP= g++
FILES_PATH= ./runFiles_and_results
CFLAGS= -g -ansi -pedantic#Extra flags to give to the C compiler.
OBJS= parser_t.o tokenizer_t.o analyzer_t.o main.o

.PHONY: all clean

$(TARGET): $(OBJS)
	$(CPP) $(OBJS) $(CFLAGS) -o $(TARGET)

parser_t.o: parser_t.cpp
	$(CPP) -c $(CFLAGS) $<

tokenizer_t.o: tokenizer_t.cpp
	$(CPP) -c $(CFLAGS) $<

analyzer_t.o: analyzer_t.cpp
	$(CPP) -c $(CFLAGS) $<
	
main.o: main.cpp
	$(CPP) -c $(CFLAGS) $<

include depends
depends:
	$(CPP) -MM $(CFLAGS) $(OBJS) > depends
	
clean:
	rm -f $(TARGET) $(OBJS) #Command to remove a file.

run:
	./$(TARGET) $(FILES_PATH)/textParser.txt $(FILES_PATH)/textParser2.txt $(FILES_PATH)/Example.txt
	
