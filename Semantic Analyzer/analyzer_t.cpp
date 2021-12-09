/*
* @file: analyzer_t.cpp
* @brief: functions for cpp analyzer_t.
* @author: Inbar Barhum
* @date: 28.3.19
*/

#include "analyzer_t.h"
#include "tokenizer_t.h"
#include <set>
#include <sstream>

//CTOR
analyzer_t::analyzer_t(tokenizer_t* _tokenizer)
{
	m_tokenizer = _tokenizer;
	m_isMainFirst = false;
	m_isIf = false;
	m_isType = false;
	m_isTypeBefore = false;
	m_isOperator = false;
	m_isOperatorBefore = false;
	m_isBracket = false;
	
	m_cuntRound = 0;
	m_countCurly = 0;
	m_countSquare = 0;
	m_countPlus = 0;
	m_countMinus = 0;

	m_bracketSet.insert("(");
	m_bracketSet.insert(")");
	m_bracketSet.insert("[");
	m_bracketSet.insert("]");
	m_bracketSet.insert("{");
	m_bracketSet.insert("}");
	
	m_typeSet.insert("int");
	m_typeSet.insert("char");
	m_typeSet.insert("short");
	m_typeSet.insert("long");
	m_typeSet.insert("float");
	m_typeSet.insert("double");
	m_typeSet.insert("void");
	
	m_keywordSet.insert("if");
	m_keywordSet.insert("else");
	m_keywordSet.insert("for");
	m_keywordSet.insert("while");
	m_keywordSet.insert("class");
	m_keywordSet.insert("public");
	m_keywordSet.insert("protected");
	m_keywordSet.insert("private");
	m_keywordSet.insert("main");
	m_keywordSet.insert("const");
	m_keywordSet.insert("virtual");
	
	m_operatorSet.insert("+");
	m_operatorSet.insert("-");
	m_operatorSet.insert("=");
	m_operatorSet.insert("*");
	m_operatorSet.insert("&");
	m_operatorSet.insert("<");
	m_operatorSet.insert(">");
}


void analyzer_t::PrintError(string _error, size_t _rowNum)
{
	cout << "Error in line " << _rowNum << ": \"" << _error << "\"." << endl << endl;
}


void analyzer_t::CheckBracketsCounts()
{
	if(m_cuntRound != 0)
	{
		cout << "Brackets error: " << m_cuntRound << " '(' not close." << endl;
	}
	if(m_countSquare != 0)
	{
		cout << "Brackets error: " << m_countSquare << " '[' not close." << endl;
	}
	if(m_countCurly != 0)
	{
		cout << "Brackets error: " << m_countCurly << " '{' not close." << endl << endl;
	}
}


void analyzer_t::CheckOperator(string _token, size_t _rowNum)
{
	if(m_operatorSet.find(_token) != m_operatorSet.end()) //chaeck if token is an operator
	{
		m_isOperator = true;
		if(_token == "+")
		{			
			m_countMinus = 0;
			m_countPlus++;
			if(m_countPlus>=3)
			{
				PrintError("Illegal operator '+++'", _rowNum);
				m_countPlus = 0;
			}
		}
		else if(_token == "-")
		{
			m_countPlus = 0;
			m_countMinus++;
			if(m_countMinus>=3)
			{
				PrintError("Illegal operator '---'", _rowNum);
				m_countMinus = 0;
			}
		}
	}
	else
	{
		m_countPlus = 0;
		m_countMinus = 0;	
	}
}


void analyzer_t::CheckType(string _token, size_t _rowNum)
{
	if(m_typeSet.find(_token) != m_typeSet.end())
	{
		m_isType = true;
		
		if(m_isTypeBefore)
		{
			ostringstream types;
			types << "Multiple types consecutively: " << m_prevToken << " and " << _token;
			PrintError(types.str(), _rowNum);
			m_isTypeBefore = false;
		}
		else
		{
			m_isTypeBefore = true;
		}
	}
}


//check if token is a legal variable.
void analyzer_t::CheckVariable(string _token, size_t _rowNum)
{
	bool isKeyword = false;
	bool isDigitStart = false;
	bool isDeclared = false;
	ostringstream variableMsg;

	if(isdigit(_token[0])) //check if var is legal (not a digit in the beginning)
	{
		isDigitStart = true;
	}	
	else if(m_keywordSet.find(_token) != m_keywordSet.end()) //check if var is legal (not a keyword)
	{
		isKeyword = true;
	}
	
	isDeclared = (m_varSet.find(_token) != m_varSet.end());
	
	if(m_isTypeBefore)
	{
		if(isDigitStart==false && isKeyword==false) //check if var is legal
		{
			//is legal
			if(isDeclared) //check if already been declared
			{
				variableMsg << "Variable '" << _token << "' has already been declared";
				PrintError(variableMsg.str(), _rowNum);
			}				
			else
			{
				m_varSet.insert(_token); //insert new variable to set
			}
		}
		else
		{	
			//is illegal
			variableMsg << "Variable '" << _token << "' is illegal (starts with a digit/is a keyword name)";
			PrintError(variableMsg.str(), _rowNum);
		}
	}
	else if(isDigitStart==false && isKeyword==false && isDeclared==false && _token != ";" && _token != ",") //legal variable is missing a type before it
	{
		variableMsg << "Variable '" << _token << "' is not declared, missing a type before";
		PrintError(variableMsg.str(), _rowNum);
	}
	m_isTypeBefore = false;
}


void analyzer_t::CheckBrackets(string _token, size_t _rowNum)
{
	if(m_bracketSet.find(_token) != m_bracketSet.end())
	{
		m_isBracket = true;
		if(_token == "(")
		{
			m_cuntRound++;
		}
		
		if(_token == "[")
		{
			m_countSquare++;
		}

		if(_token == "{")
		{
			m_countCurly++;
		}
		
		if(_token == ")")
		{
			if(m_cuntRound == 0)
			{
				PrintError("')' without '('", _rowNum);
			}
			else
			{
				m_cuntRound--;
			}
		}
		
		if(_token == "]")
		{
			if(m_countSquare == 0)
			{
				PrintError("']' without '['", _rowNum);
			}
			else
			{
				m_countSquare--;
			}
		}

		if(_token == "}")
		{
			if(m_countCurly == 0)
			{
				PrintError("'}' without '{'", _rowNum);
			}
			else
			{
				m_countCurly--;
			}
		}
	}
}

void analyzer_t::ResetAnalyzer()
{
	m_isMainFirst = false;
	m_isIf = false;
	m_isType = false;
	m_isTypeBefore = false;
	m_isOperator = false;
	m_isOperatorBefore = false;
	m_isBracket = false;
	
	m_cuntRound = 0;
	m_countCurly = 0;
	m_countSquare = 0;
	m_countPlus = 0;
	m_countMinus = 0;
	
	m_varSet.clear(); //clear variables set content for next file parsing
}

void analyzer_t::RunAnalyzer(size_t _rowNum)
{
	while(1)
	{
		m_isType = false;
		m_isOperator = false;
		m_isBracket = false;
		
		if(m_tokenizer->IsEmpty())
		{
			break;
		}
		string token = m_tokenizer->GetNextToken();

		//check main
		if(m_isMainFirst == false)
		{
			if(token != "main")
			{
				PrintError("There is a declaration before first 'main'", _rowNum);
			}
			else
			{
				m_prevToken = token;
				continue;
			}
			m_isMainFirst = true;
		}
		
		//check if
		if(token == "if")
		{
			m_isIf = true;
			m_prevToken = token;
			continue;
		}
		
		//check else
		if(token == "else")
		{
			if(m_isIf == false)
			{
				PrintError("There is 'else' without 'if'", _rowNum);
			}
			m_prevToken = token;
			continue;
		}
		
		CheckBrackets(token, _rowNum);
		if(m_isBracket)
		{
			m_prevToken = token;
			continue;		
		}
		
		CheckOperator(token, _rowNum);
		if(m_isOperator)
		{
			m_prevToken = token;
			continue;		
		}
		
		CheckType(token, _rowNum);
		if(m_isType)
		{
			m_prevToken = token;
			continue;		
		}

		CheckVariable(token, _rowNum);
		m_prevToken = token;
	}
}

