/*
* @file: parser_t.cpp
* @brief: functions for cpp parser_t.
* @author: Inbar Barhum
* @date: 27.3.19
*/

#include "parser_t.h"
#include "tokenizer_t.h"
#include "analyzer_t.h"

//default CTOR
parser_t::parser_t()
{
	const string delimiters = "()[]{};<>=+-*&\r\n\t\v ";
	m_tokenizer = new tokenizer_t(delimiters);
	m_analyzer = new analyzer_t(m_tokenizer);
}


//DTOR
parser_t::~parser_t()
{
	delete m_analyzer;
	delete m_tokenizer;
}


void parser_t::ResetParser()
{
	m_analyzer->ResetAnalyzer(); // call reset the analyzer variables;
	m_pfile.close();
	cout << "**Reset parser for next file**" << endl;
	cout << "--------------------------------------------------------------" << endl << endl;
}


void parser_t::RunParser(const string& _pathName)
{
	size_t lineCount = 1;
	
	//default for ifstream is read mode ios::in
	m_pfile.open(_pathName.c_str());

	string line;
	if(m_pfile.is_open())
	{
		cout << "Open file: '" << _pathName << "' succeeded!" << endl << endl;
		while(1)
		{
			getline(m_pfile, line);
			if(!m_pfile.eof()) //read until EOF
			{
				m_tokenizer->TokenzieLine(line);
				m_analyzer->RunAnalyzer(lineCount); //will call func from tokenizer
				lineCount++;
			}
			else
			{
				break;
			}
		}
		m_analyzer->CheckBracketsCounts();
		ResetParser();
	}
	else
	{
		cout << "Error: File '" << _pathName << "' can't be opened. " << endl << endl;
		return;
	}
}

