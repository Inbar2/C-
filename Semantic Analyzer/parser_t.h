/*
 * @file: parser_t.h
 * @brief: functions signatures for parser_t.
 * @author: Inbar Barhum
 * @date: 27.3.19
 */

/*
g++ -g -ansi -pedantic *.cpp
./a.out textParser.txt textParser2.txt
*/

#ifndef __PARSER_T_H__
#define __PARSER_T_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

//forward decleration
class tokenizer_t;
class analyzer_t;

class parser_t
{
	public:
		parser_t();								//default CTOR
		virtual ~parser_t();					//DTOR
								
		virtual void RunParser(const string& _pathName); //function to start running the parser
	
	
	protected:
		ifstream m_pfile;
		tokenizer_t* m_tokenizer; //pointer will make it possible to access optional derived classes of tokenizer.
		analyzer_t* m_analyzer;

		void ResetParser();

	private:

		parser_t(const parser_t& _parser);
		parser_t& operator=(const parser_t& _parser);
};

#endif // parser_t.h

