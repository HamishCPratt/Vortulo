#ifndef _PARSER_HPP
#define _PARSER_HPP

#include <iostream> 
#include <string>  
#include "Filter.hpp"

enum class Tense {present, future, past, conditional, infinitive};  

class Parser
{	
private:
	Filter* parserFilter;
public:
	Parser();
	Parser(Filter*);
	~Parser();
	void setFilter(Filter*);
	
	bool pluralChance();
		
	std::string sentenceGeneraion();
	
	//List of functions for generating the different fragments of sentences
	std::string simpleIndCl();
	std::string simpleDepCl();
	std::string simpleDepIndCl();
	std::string relativeCl();
	std::string relativeClStart();
	
	//List of functions that return a word from the filter class
	std::string articleCall();
	std::string objectCall(bool accusative, bool plural);
	std::string objectGroup(bool accusative);
	std::string pronounCall();
	std::string adverbCall();
	std::string verbCall();
	std::string nounCall();
	std::string adjectiveCall();
	std::string subordCongCall();
	std::string relativeAdverbCall();
	std::string relativePronounCall();
	std::string prepositionCall();
	std::string verbTenseCall();
	
	Tense tenseSelect();
	std::string tenseCorrect(std::string, Tense);
};

#endif // _PARSER_HPP
