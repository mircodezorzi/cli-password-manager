#ifndef LOGGER_H_H3RB85EA
#define LOGGER_H_H3RB85EA

#include <fstream>

#define debugLevel 1
#define infoLevel 2
#define warningLevel 3
#define errorLevel 4
#define criticalLevel 5

class Logger{

public:
    Logger(std::string logPath, size_t thresholdLevel = 0, \
	   std::string messageFormat = "%(date) - %(time) - %(level) - %(msg)");
    
    void setLevel(size_t thresholdLevel)      {mLevel  = thresholdLevel;}
    void setFormat(std::string messageFormat) {mFormat = messageFormat;}
    void setLogFilepath(std::string logPath)  {mPath   = logPath;}
	
    size_t	getLevel()		      {return mLevel;}
    std::string getFormat()		      {return mFormat;}
    std::string getLogPath()		      {return mPath;}

    // General logging function
    void log(size_t level, std::string message);
  
    // Specific logging function with different priority levels
    void debug(std::string message);
    void info(std::string message);
    void warning(std::string message);
    void error(std::string message);
    void critical(std::string message);

private:
    std::ofstream logStream;
    
    // Used to format message passed in log functions
    std::string formatMessage(std::string message); 
    std::string getDate(std::string format = "DD-MM-YYYY hh:mm:ss");

    // Threshold for logger
    size_t mLevel;
    
    std::string mFormat;  
    std::string mPath;
};

#endif /* end of include guard: LOGGER_H_H3RB85EA */
