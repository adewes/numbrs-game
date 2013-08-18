#ifndef _LOGGER
#define _LOGGER 1

#include "singleton.h"
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include<streambuf>
#include<sstream>

using namespace std;

class Logger : public Singleton <Logger>
{
public:
	~Logger();
	void Setup();
	std::string LogTime();
	void Error(std::string msg);
	void Event(std::string msg);
	void Game(std::string msg);
	void Script(std::string msg);
	void PlainScript(std::string msg);
private:
	ofstream ErrorHandle,EventHandle,GameHandle,ScriptHandle;
};

#endif
