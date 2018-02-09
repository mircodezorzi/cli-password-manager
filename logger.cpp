#include "logger.h"

#include <fstream>
#include <ios>
#include <string>
#include <ctime>

Logger::Logger(std::string logFilepath, size_t thresholdLevel, std::string messageFormat){ 
    mPath   = logFilepath;
    mFormat = messageFormat;
    mLevel  = thresholdLevel;

    logStream.open(mPath, std::ios_base::app | std::ios_base::out);
}

std::string Logger::formatMessage(std::string message){
    // TODO complete function

    time_t t = time(0);
    struct tm *pCurrentDate = localtime(&t);
    
    std::string date = std::to_string(pCurrentDate->tm_year + 1900) + "-" + \
	               std::to_string(pCurrentDate->tm_mon + 1) + "-" + \
		       std::to_string(pCurrentDate->tm_mday);
    std::string time = std::to_string(pCurrentDate->tm_hour) + ":" + \
		       std::to_string(pCurrentDate->tm_min) + ":" + \
		       std::to_string(pCurrentDate->tm_sec);

    std::string formattedString = date + " " + time + " - " + message + "\n";
    return formattedString;
}

// TODO move these functions to .h since there's no need of having them here
void Logger::log(size_t level, std::string message){
    if(level >= mLevel) logStream << formatMessage(message);
}

void Logger::debug(std::string message){
    if(debugLevel >= mLevel) logStream << formatMessage(message);
}

void Logger::info(std::string message){
    if(infoLevel >= mLevel) logStream << formatMessage(message);
}

void Logger::warning(std::string message){
    if(warningLevel >= mLevel) logStream << formatMessage(message);
}

void Logger::error(std::string message){
    if(errorLevel >= mLevel) logStream << formatMessage(message);
}

void Logger::critical(std::string message){
    if(criticalLevel >= mLevel) logStream << formatMessage(message);
}
