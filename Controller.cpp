#include <iostream>
#include <string>     
#include "Controller.hpp"

Controller::Controller()
{
	srand (time(NULL));
	parser = new Parser();
	filter = new Filter();
}

Controller::~Controller(){}

void Controller::startProg()
{
	filter->filterWords();
	parser->setFilter(filter);
	std::cout << parser->sentenceGeneraion() << std::endl;
}

