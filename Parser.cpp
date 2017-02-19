#include <iostream>
#include <string>     
#include "Parser.hpp"
#include "Filter.hpp"

Parser::Parser(){}

Parser::Parser(Filter* infilter)
{
	parserFilter = infilter;
}

void Parser::setFilter(Filter* inFilter)
{
	parserFilter = inFilter;
}

Parser::~Parser() {}

std::string Parser::sentenceGeneraion()
{
	//Mulitple types of sentences to generate
	int choice = rand() % 3;
	if (choice == 0)
	{
		return simpleDepIndCl();
	}
	else if (choice == 1)
	{
		return simpleIndCl();
	}
	else if (choice == 2)
	{
		return relativeClStart() + ", " + relativeCl();
	}	
}

//Simple dependant clause
std::string Parser::simpleDepCl()
{
	std::string sent = "";
	sent += subordCongCall() + " ";
	sent += objectGroup(false) + " " + verbTenseCall();
	return sent;
	
}

//Simple independant clause
std::string Parser::simpleIndCl()
{
	std::string sent = "";
	int choice = rand() % 2;
	//Pronoun or noun as the actor in the sentence
	if (choice == 0)
	{
		sent += objectGroup(false) + " ";	
	}
	else if (choice == 1)
	{
		sent += pronounCall() + " ";
	}
	//Addition of an adverb
	choice = rand() % 15;
	if (choice == 0)
	{
		sent += adverbCall() + " ";
	}
	choice = rand() % 2;
	sent += verbTenseCall(); 
	if (choice == 0)
	{
		return sent;
	}
	//Object being acted upon by the actor
	else if (choice == 1)
	{
		choice = rand() % 2;
		if (choice == 0)
		{
			sent += " " + objectGroup(true);
		}
		else
		{
			sent += " " + prepositionCall() + " " + objectGroup(true);
		}
		return sent;
	}

}

std::string Parser::simpleDepIndCl()
{
	return (simpleDepCl() + ", " + simpleIndCl());
}

std::string Parser::articleCall()
{
	int choice = rand() % 3;
	if (choice == 0)
	{
		return "la";
	}
	else if (choice == 1)
	{
		return pronounCall()+"a";
	}
	else
	{
		return "";
	}
}

//Returns one or many nouns stringed together in a list
std::string Parser::objectGroup(bool accusative)
{
	std::string obj;
	int choice = rand() % 100;
	choice -= 95;
	//More nouns in the list
	if (choice > 5)
	{
		for (int i = 0; i < choice; i++)
		{
			if (i = choice - 1)
			{
				obj += " kaj " + objectCall(accusative, pluralChance());
			}
			else
			{
				obj += ", " + objectCall(accusative, pluralChance());
			}
		}
	}
	//Just one noun
	else
	{
		obj = objectCall(accusative, pluralChance());
	}
	return obj;
}

//Returns a single noun (with possible adjectives)
std::string Parser::objectCall(bool accusative, bool plural)
{
	std::string obj = "";
	std::string newArt = articleCall();
	//Adding plural and accusative to the article
	if (newArt != "")
	{
		if (newArt != "la" && newArt != "")
		{
			if (plural)
			{
				newArt += "j";
			}
			if (accusative)
			{
				newArt += "n";
			}
		}
		obj += newArt + " ";
	}
	int choice = rand() % 2;
	//Adding plural and accusative to the adjective
	if (choice == 0)
	{
		obj += adjectiveCall();
		if (plural)
		{
			obj += "j";
		}
		if (accusative)
		{
			obj += "n";
		}
		int prob = 2;
		int adjChoice = rand() % prob;
		//An additional adjective
		while (adjChoice = 0)
		{
			int adjChoice = rand() % prob;
			obj += " " + adjectiveCall();
			if (plural)
			{
				obj += "j";
			}
			if (accusative)
			{
				obj += "n";
			}
		}
		obj += " "; 
	}
	obj += nounCall();
	//Adding plural and accusative to the noun
	if (plural)
	{
		obj += "j";
	}
	if (accusative)
	{
		obj += "n";
	}
	return obj;
}

//If the instance should be plural
bool Parser::pluralChance()
{
	int pluralChoice = rand() % 2;
	bool plural = false;
	if (pluralChoice == 0)
	{
		plural = true;
	}
	return plural;
}

Tense Parser::tenseSelect()
{
	std::vector<Tense> tenseChoice = {Tense::present, Tense::future, Tense::past, Tense::conditional, Tense::infinitive};  
	int loc = rand() % tenseChoice.size();
	return tenseChoice[loc];	
}

//Updates a verb to the passed tense
//Easily modified in esperanto
std::string Parser::tenseCorrect(std::string verb, Tense type)
{
	int lastLoc = verb.length()-1;
	if (type == Tense::present)
	{
		verb[lastLoc] = 'a';
		return verb + "s";
	}
	else if (type == Tense::past)
	{
		return verb + "s";
	}
	else if (type == Tense::future)
	{
		verb[lastLoc] = 'o';
		return verb + "s";
	}
	else if (type == Tense::infinitive)
	{
		return verb;
	}
	else if (type == Tense::conditional)
	{
		verb[lastLoc] = 'u';
		return verb + "s";
	}
}

//Relative Clause Start
std::string Parser::relativeClStart()
{
	int choice = rand() % 2;
	if (choice == 0)
	{
		return "ĉi tiu estas " + objectGroup(false);	
	}
	else
	{
		return "tiu estas " + objectGroup(false);	
	}
}

//Relative Clause
std::string Parser::relativeCl()
{
	int choice = rand() % 4;

	if (choice == 0)
	{
		return relativePronounCall() + " " + objectGroup(false) + " " + verbTenseCall();
	}
	else if (choice == 1)
	{
		return relativeAdverbCall() + " " + objectGroup(false) + " " + verbTenseCall();
	}
	else if (choice == 2)
	{
		return "kiu " + verbCall();
	}
	else if (choice == 3)
	{
		return "kiun " + objectGroup(false) + " " + verbTenseCall() + " " + prepositionCall();
	}
}

std::string Parser::verbTenseCall()
{
	//Avoid the infinite case
	Tense tense = tenseSelect();
	while (tense == Tense::infinitive)
	{
		tense = tenseSelect();
	}
	int choice = rand() % 2;
	if (choice == 0)
	{
		return "ne " + tenseCorrect(verbCall(), tense);
	}
	else
	{
		return tenseCorrect(verbCall(), tense);
	}
}

std::string Parser::pronounCall()
{
	return parserFilter->request(WordType::pronoun);
}

std::string Parser::adverbCall()
{
	return parserFilter->request(WordType::adverb);
}

std::string Parser::verbCall()
{
	return parserFilter->request(WordType::verb);
}

std::string Parser::nounCall()
{
	return parserFilter->request(WordType::noun);
}

std::string Parser::adjectiveCall()
{
	return parserFilter->request(WordType::adjective);
}

std::string Parser::subordCongCall()
{
	return parserFilter->request(WordType::subord);
}

std::string Parser::relativeAdverbCall()
{
	return parserFilter->request(WordType::relativeAdverb);
}

std::string Parser::relativePronounCall()
{
	return parserFilter->request(WordType::relativePronoun);
}

std::string Parser::prepositionCall()
{
	return parserFilter->request(WordType::preposition);
}


