#include "logger.h"

#include <fstream>
#include <ios>
#include <string>
#include <ctime>

Logger::Logger(std::string logPath, size_t thresholdLevel, std::string messageFormat){ 
    mPath   = logPath;
    mLevel  = thresholdLevel;
    mFormat = messageFormat;

    logStream.open(mPath, std::ios_base::app | std::ios_base::out);
}

void Logger::replace(std::string &str, std::string substr, std::string replacestr){
    if(str.find(substr) != -1)
	str.replace(str.find(substr), substr.length(), replacestr);
}

std::string Logger::getDate(std::string format){ 
    time_t t = time(0);
    struct tm *pCurrentDate = localtime(&t);    
    
    replace(format, "DD",   std::to_string(pCurrentDate->tm_mday));
    replace(format, "MM",   std::to_string(pCurrentDate->tm_mon + 1));
    replace(format, "YYYY", std::to_string(pCurrentDate->tm_year + 1900));
    replace(format, "hh",   std::to_string(pCurrentDate->tm_hour));
    replace(format, "mm",   std::to_string(pCurrentDate->tm_min));
    replace(format, "ss",   std::to_string(pCurrentDate->tm_sec));

    return format;
}

std::string Logger::formatMessage(std::string message){
    std::string formattedMessage = mFormat;
    replace(formattedMessage, "%(date)",  getDate("DD-MM-YYYY"));
    replace(formattedMessage, "%(time)",  getDate("hh:mm:ss"));
    replace(formattedMessage, "%(level)", std::to_string(mLevel));
    replace(formattedMessage, "%(msg)",   message);
    return formattedMessage + "\n";
}

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
