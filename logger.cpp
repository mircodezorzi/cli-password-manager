#include "logger.h"
#include "utilities.h"
#include "timeDate.h"

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
    using namespace utilities;
    std::string formattedMessage = mFormat,
		timeFormat = substring(mFormat, "{time", "}"),
		dateFormat = substring(mFormat, "{date", "}");
    replace(formattedMessage, "{date}",  TimeDate::instantToString(TimeDate::now(), dateFormat));
    replace(formattedMessage, "{time}",  TimeDate::instantToString(TimeDate::now(), timeFormat));
    replace(formattedMessage, "{level}", level);
    replace(formattedMessage, "{message}",   message);
    return formattedMessage + "\n";
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
