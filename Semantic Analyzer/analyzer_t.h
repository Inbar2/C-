/*
 * @file: analyzer_t.h
 * @brief: functions signatures for analyzer_t.
 * @author: Inbar Barhum
 * @date: 28.3.19
 */

#ifndef __ANALYZER_T_H__
#define __ANALYZER_T_H__

#include <iostream>
#include <string>
#include <set>

using namespace std;

//forward decleration
class tokenizer_t;

class analyzer_t
{
	public:
		analyzer_t(tokenizer_t* _tokenizer);				//CTOR
		virtual ~analyzer_t(){}								//DTOR	

		void RunAnalyzer(size_t rowNum);
		void CheckBracketsCounts();
		void ResetAnalyzer();
	
	protected:
		void CheckBrackets(string token, size_t _rouNum);
		void PrintError(string _error, size_t _rowNum);
		void CheckType(string _token, size_t _rowNum);
		void CheckVariable(string _token, size_t _rowNum);
		void CheckOperator(string _token, size_t _rowNum);

	private:
		tokenizer_t* m_tokenizer;
		bool m_isMainFirst;
		bool m_isIf;
		bool m_isType;
		bool m_isTypeBefore;
		bool m_isOperator;
		bool m_isOperatorBefore;
		bool m_isBracket;
		
		int m_cuntRound;
		int m_countCurly; 
		int m_countSquare;
		size_t m_countPlus;
		size_t m_countMinus;
		
		string m_prevToken;
		
		set<string> m_varSet;
		set<string> m_bracketSet;
		set<string> m_typeSet;
		set<string> m_keywordSet;
	 	set<string> m_operatorSet;
 
		analyzer_t(const analyzer_t& _analyzer);
		analyzer_t& operator=(const analyzer_t& _analyzer);
};

#endif // analyzer_t.h

