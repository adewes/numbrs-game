#include "logger.h"

void Logger::Setup()
{
	ErrorHandle.open ( "log/error.log",ios::trunc );
	EventHandle.open ( "log/event.log",ios::trunc );
	GameHandle.open ( "log/game.log",ios::trunc );
	ScriptHandle.open ( "log/lua.log",ios::trunc );
	Error("Starting error log.");
	Game("Starting game log.");
	Event("Starting event log.");
	Script("Starting scripting log.");
	
	std::cout.rdbuf(EventHandle.rdbuf());
	std::cerr.rdbuf(ErrorHandle.rdbuf());

	cerr << "This is just a test...\n";
	cout << "Another test...\n";

}

std::string Logger::LogTime()
{
	char *timestring;
	time_t currentTime;
	time (&currentTime);
	timestring=ctime(&currentTime);
	timestring[strlen(timestring)-1]=0x0;
	return timestring;
}


Logger::~Logger()
{
	ErrorHandle.close();
	EventHandle.close();
	GameHandle.close();
	ScriptHandle.close();
}

void Logger::Script(std::string msg)
{
	ScriptHandle << LogTime() << ": " << msg << "\n";
	ScriptHandle.flush();
}

void Logger::PlainScript(std::string msg)
{
	ScriptHandle << msg ;
	ScriptHandle.flush();
}

void Logger::Error(std::string msg)
{
	ErrorHandle << LogTime() << ": " << msg << "\n";
	ErrorHandle.flush();
}

void Logger::Event(std::string msg)
{
	EventHandle << LogTime() << ": " << msg << "\n";
	EventHandle.flush();
}

void Logger::Game(std::string msg)
{
	GameHandle << LogTime() << ": " << msg << "\n";
	GameHandle.flush();
}
