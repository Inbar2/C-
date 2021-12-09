/*
 * @file: tokenizer_t.h
 * @brief: functions signatures for tokenizer_t.
 * @author: Inbar Barhum
 * @date: 27.3.19
 */

#ifndef __TOKENIZER_T_H__
#define __TOKENIZER_T_H__

#include <iostream>
#include <string>
#include <queue> //queue

using namespace std;

class tokenizer_t
{
	public:
		tokenizer_t(const string& _delimiters):m_delimiters(_delimiters) {};	//CTOR
		virtual ~tokenizer_t(){} 												//DTOR

		void TokenzieLine(const string& _line);
		string GetNextToken();
		bool IsEmpty() const;
		
		//for debugging
		void PrintItems();
	
	private:
		queue<string> m_tQueue;
		const string m_delimiters;
		
		tokenizer_t(const tokenizer_t& _tokenizer);
		const tokenizer_t& operator=(const tokenizer_t& _tokenizer);
};

#endif // tokenizer_t.h

