/*
* @file: tokenizer_t.cpp
* @brief: functions for cpp tokenizer_t.
* @author: Inbar Barhum
* @date: 28.3.19
*/

#include "tokenizer_t.h"

string tokenizer_t::GetNextToken()
{
	string myToken;

	myToken = m_tQueue.front();
	m_tQueue.pop();
	
	return myToken;	
}

bool tokenizer_t::IsEmpty() const
{
	m_tQueue.empty() ? true : false;	
}


//for test
void tokenizer_t::PrintItems()
{
	size_t i=0;
	int size = m_tQueue.size();
	
	for(i=0; i<size; i++)
	{
		cout << m_tQueue.front() << endl;
		m_tQueue.pop();
		
	}
}

void tokenizer_t::TokenzieLine(const string& _line)
{
	int sPos = 0;
	int cPos = 0;
	string token;
	size_t length = _line.length();

	while(sPos < length) //if line is empty will also finish
	{
		cPos = _line.find_first_of(m_delimiters, sPos);

		if(cPos>=0) //delimiter was found
		{
			if(sPos!=cPos)
			{
				token = _line.substr(sPos, cPos-sPos);
				m_tQueue.push(token);
			}
			if(!isspace(_line[cPos]))  //if delimiter is a token
			{
				token = _line.substr(cPos, 1);
				m_tQueue.push(token);
			}
			
			sPos = cPos+1;
		}
		else
		{
			if(sPos<length)
			{
				token = _line.substr(sPos, length-sPos);
				m_tQueue.push(token);
			}
			break;
		}
	}
	
	//for debug
	//PrintItems();
}

