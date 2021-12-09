// test tokenizer_t;
/*
 * @file: main.cpp
 * @brief: main for parser exercise.
 * @author: Inbar Barhum
 * @date: 27.3.19
 */

#include <iostream>
#include "parser_t.h"


int main(int argc, char* argv[])
{
	parser_t parser;

	int i;

	for(i=1; i<argc; i++)
	{
		cout << "File name: " << argv[i] << endl; 
		
		parser.RunParser(argv[i]);
	}
	
	return 0;
}


