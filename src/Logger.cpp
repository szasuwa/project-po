#include "Logger.h"

void LogError(const std::string& error)
{
	std::cout << "[Error] " << error << std::endl;
}

void LogInfo(const std::string& error)
{
	std::cout << "[Info] " << error << std::endl;
}