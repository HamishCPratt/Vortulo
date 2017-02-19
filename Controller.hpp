#ifndef _CONTROLLER_HPP
#define _CONTROLLER_HPP

#include <iostream> 
#include <string>  
#include "Parser.hpp"
#include "Filter.hpp"

class Controller 
{
private:
	Filter* filter;
	Parser* parser;
public:
	Controller();
	~Controller();
	
	void startProg();
};
#endif //_CONTROLLER_HPP
