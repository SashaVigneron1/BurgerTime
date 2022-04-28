#include "PeakAEnginePCH.h"
#include "Logger.h"

Logger::ConsoleColor Logger::defaultColor = Logger::ConsoleColor::White;

void Logger::LogError(const char* message, const char* errormsg)
{
	SetConsoleColor(ConsoleColor::LightRed);
	std::string string;
	string.append(message);
	std::cerr << string.append(errormsg) << std::endl;
	SetConsoleColor(defaultColor);
}
