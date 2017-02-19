#ifndef _FILTER_HPP
#define _FILTER_HPP

#include <iostream> 
#include <string>  
#include <vector>

enum class WordType { verb, noun, pronoun, adverb, adjective, other, subord, relativePronoun, relativeAdverb, preposition };  

class Filter
{
	//Vector of each type of word
	std::vector<std::string> verbList;
	std::vector<std::string> nounList;
	std::vector<std::string> pronounList;
	std::vector<std::string> adverbList;
	std::vector<std::string> adjectiveList;
	std::vector<std::string> otherList;
	std::vector<std::string> prepositionList;
	std::vector<std::string> correlativeList;
	std::vector<std::string> subordCongList;
	std::vector<std::string> relativePronounList;
	std::vector<std::string> relativeAdverbList;
	
	
public:
	Filter();
	~Filter();
	
	//Separate the words into their catergories
	void filterWords();
	
	void printVector(std::vector<std::string>);
	
	//Checks if a word is already apart of another list. 
	bool inList(std::string, std::vector<std::string>);
	
	//Returns a random word of WordType 
	std::string request(WordType); 
};
#endif //_FILTER_HPP
