#include "logger.h"

#include <fstream>
#include <string>
#include <ctime>
#include <ios>

Logger::Logger(std::string filepath, size_t threshold, std::string format){ 
    mPath      = filepath;
    mThreshold = threshold;
    mFormat    = format;
    
    logStream.open(mPath, std::ios_base::app | std::ios_base::out);
}

std::string Logger::formatMessage(std::string message, std::string level){
    std::string formattedMessage = mFormat;
    replace(formattedMessage, "%(date)",  getDate("DD-MM-YYYY"));
    replace(formattedMessage, "%(time)",  getDate("hh:mm:ss"));
    replace(formattedMessage, "%(level)", level);
    replace(formattedMessage, "%(msg)",   message);
    return formattedMessage + "\n";
}

std::string Logger::getDate(std::string format){ 
    time_t t = time(0); 
    struct tm *pCurrent = localtime(&t);        
    replace(format, "DD",   std::to_string(pCurrent->tm_mday));
    replace(format, "MM",   std::to_string(pCurrent->tm_mon + 1));
    replace(format, "YYYY", std::to_string(pCurrent->tm_year + 1900));
    replace(format, "hh",   std::to_string(pCurrent->tm_hour));
    replace(format, "mm",   std::to_string(pCurrent->tm_min));
    replace(format, "ss",   std::to_string(pCurrent->tm_sec));
    return format;
}

void Logger::replace(std::string& str, std::string substr, std::string replacement){
    if(str.find(substr) != -1)
	str.replace(str.find(substr), substr.length(), replacement);
}

void Logger::log(size_t level, std::string message){
    if(level >= mThreshold)	    logStream << formatMessage(message, "log");
}

void Logger::debug(std::string message){
    if(debugLevel >= mThreshold)    logStream << formatMessage(message, "debug");
}

void Logger::info(std::string message){
    if(infoLevel >= mThreshold)	    logStream << formatMessage(message, "info");
}

void Logger::warning(std::string message){
    if(warningLevel >= mThreshold)  logStream << formatMessage(message, "warning");
}

void Logger::error(std::string message){
    if(errorLevel >= mThreshold)    logStream << formatMessage(message, "error");
}

void Logger::critical(std::string message){
    if(criticalLevel >= mThreshold) logStream << formatMessage(message, "critical");
}
