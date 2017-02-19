#include <iostream>
#include <string>     
#include "Filter.hpp"
#include <fstream>
#include <sstream>


Filter::Filter()
{
	//Set up the word exceptions in Esperanto
	std::vector<std::string> pronounExceptions = {"li","ŝi","mi","ĝi", "vi", "si", "ni", "ili"};
	for (int i = 0; i < pronounExceptions.size(); i++)
	{
		pronounList.push_back(pronounExceptions[i]);
	}
	std::vector<std::string> otherExceptions = {"ke", "ne", "se", "tre", "ja"};
	for (int i = 0; i < otherExceptions.size(); i++)
	{
		otherList.push_back(otherExceptions[i]);
	}
	
	std::vector<std::string> prepositionExceptions = {"super", "trans", "post", "kontraŭ", "inter", "kiel", "ĉe", "de", "je", "dum", "en", "per", "kun", "pri"};
	for (int i = 0; i < prepositionExceptions.size(); i++)
	{
		prepositionList.push_back(prepositionExceptions[i]);
	}
	std::vector<std::string> correlativeExceptions = {"kia", "kio", "kiu", "tio", "tia", "tiu"};
	for (int i = 0; i < correlativeExceptions.size(); i++)
	{
		correlativeList.push_back(correlativeExceptions[i]);
	}
	std::vector<std::string> subordCongExceptions = {"post", "kiel", "kvankam", "kvazaŭ", "ĉar", "antaŭ", "eĉ se", "ekde", "tiel", "tiel ke", "ĝis", "kiam", "kie", "dum"};
	for (int i = 0; i < subordCongExceptions.size(); i++)
	{
		subordCongList.push_back(subordCongExceptions[i]);
	}
	relativeAdverbList = {"kial", "kie", "kiam"};
	relativePronounList = {"ke", "kiun", "kiu", "kies"};		
}

Filter::~Filter(){}

void Filter::printVector(std::vector<std::string> vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (i != vec.size()-1)
		{
			std::cout << vec[i] << " ";
		}
		else
		{
			std::cout << vec[i] << std::endl;
		}
	}
}

bool Filter::inList(std::string checkWord, std::vector<std::string> checkList)
{
	for (int i = 0; i < checkList.size(); i++)
	{
		if (checkWord == checkList[i])
		{
			return true;
		}
	}
	return false;
}


void Filter::filterWords()
{
	std::ifstream infile("wordList.txt");
	std::string line;
	//Filter the words based on the last letter
	//Aspect of Esperanto that allows for word identification
	while (std::getline(infile, line))
	{
		int lastLoc = line.length()-1;
		if (!inList(line, pronounList) && !inList(line, otherList) && !inList(line, prepositionList))
		{ 
			if (line[lastLoc] == 'o')
			{
				nounList.push_back(line);
			}
			else if(line[lastLoc] == 'a')
			{
				adjectiveList.push_back(line);
			}
			else if(line[lastLoc] == 'e' || line[lastLoc] == 'ŭ')
			{
				adverbList.push_back(line);
			}
			else if (line[lastLoc] == 'i')
			{
				verbList.push_back(line);
			}
			else
			{
				otherList.push_back(line);
			}
		}
	}
}

std::string Filter::request(WordType wordRequest)
{
	std::string returnWord = "";
	if (wordRequest == WordType::verb)
	{
		int loc = rand() % verbList.size();
		returnWord = verbList[loc];
	}
	else if (wordRequest == WordType::noun)
	{
		int loc = rand() % nounList.size();
		returnWord = nounList[loc];
	}
	else if (wordRequest == WordType::pronoun)
	{
		int loc = rand() % pronounList.size();
		returnWord = pronounList[loc];
	}
	else if (wordRequest == WordType::adverb)
	{
		int loc = rand() % adverbList.size();
		returnWord = adverbList[loc];
	}
	else if (wordRequest == WordType::adjective)
	{
		int loc = rand() % adjectiveList.size();
		returnWord = adjectiveList[loc];
	}
	else if (wordRequest == WordType::other)
	{
		int loc = rand() % otherList.size();
		returnWord = otherList[loc];
	}
	else if (wordRequest == WordType::subord)
	{
		int loc = rand() % subordCongList.size();
		returnWord = subordCongList[loc];
	}
	else if (wordRequest == WordType::relativePronoun)
	{
		int loc = rand() % relativePronounList.size();
		returnWord = relativePronounList[loc];
	}
	else if (wordRequest == WordType::relativeAdverb)
	{
		int loc = rand() % relativeAdverbList.size();
		returnWord = relativeAdverbList[loc];
	}
	else if (wordRequest == WordType::preposition)
	{
		int loc = rand() % prepositionList.size();
		returnWord = prepositionList[loc];
	}
	return returnWord;
}
