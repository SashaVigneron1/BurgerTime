#pragma once
#include "FileIO.h"
#include "SingleInstance.h"

class Logger final
{
public:
	enum class ConsoleColor
	{
		Black = 0,
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Brown = 6,
		LightGray = 7,
		DarkGray = 8,
		LightBlue = 9,
		LightGreen = 10,
		LightCyan = 11,
		LightRed = 12,
		LightMagenta = 13,
		Yellow = 14,
		White = 15
	};

	static void Initialize()
	{
		// Delete Previous Data From File
		m_FileIO.DeleteAllLines();
	}

	static ConsoleColor defaultColor;
	static void LogInfo(const std::string& message)
	{
		SetConsoleColor(defaultColor);
		std::cout << message << std::endl;
		SetConsoleColor(defaultColor);
	}
	static void LogWarning(const std::string& message)
	{
		SetConsoleColor(ConsoleColor::Yellow);
		std::cout << message << std::endl;
		SetConsoleColor(defaultColor);
	}
	static void LogError(const std::string& message)
	{
		SetConsoleColor(ConsoleColor::LightRed);
		std::cerr << message << std::endl;
		SetConsoleColor(defaultColor);
	}
	static void LogError(const char* message, const char* errormsg)
	{
		SetConsoleColor(ConsoleColor::LightRed);
		std::string string;
		string.append(message);
		std::cerr << string.append(errormsg) << std::endl;
		SetConsoleColor(defaultColor);
	}
	static void LogMessage(const std::string& message, ConsoleColor color)
	{
		SetConsoleColor(color);
		std::cout << message << std::endl;
		SetConsoleColor(defaultColor);
	}
	static void LogSuccess(const std::string& message)
	{
		SetConsoleColor(ConsoleColor::LightGreen);
		std::cout << message << std::endl;
		SetConsoleColor(defaultColor);
	}
	static void LogVector(const std::string& name, float x, float y, float z)
	{
		SetConsoleColor(defaultColor);
		std::cout << name << ": " << x << ", " << y << ", " << z << ")" << std::endl;
		SetConsoleColor(defaultColor);
	}

	static void EmptyLine() { std::cout << std::endl; }

	static void ClearConsole() { system("cls"); std::cout << std::flush; }
	static void SetConsoleColor(ConsoleColor color)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, WORD(color));
	}
private:
	static FileIO m_FileIO;
};

