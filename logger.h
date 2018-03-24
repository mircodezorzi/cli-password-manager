#ifndef LOGGER_H_H3RB85EA
#define LOGGER_H_H3RB85EA

//TODO
//  fix level display: print debug/ingo/warning/error/critical instead of level: mLevel

#include <fstream>

#define debugLevel    1
#define infoLevel     2
#define warningLevel  3
#define errorLevel    4
#define criticalLevel 5

class Logger{

public:
    Logger(std::string filepath, size_t level = 0, \
	   std::string format = "%(date) - %(time) | level: %(level) | %(msg)");
    
    void setLevel (size_t l)		{mLevel  = l;}
    void setFormat(std::string f)	{mFormat = f;}
    void setPath  (std::string p)	{mPath   = p;}
	
    size_t	getLevel() const	{return mLevel;}
    std::string getFormat() const       {return mFormat;}
    std::string getPath() const		{return mPath;}

    // General logging function
    void log(size_t level, std::string message);
  
    // Specific logging function with different priority levels
    void debug	 (std::string message);
    void info	 (std::string message);
    void warning (std::string message);
    void error	 (std::string message);
    void critical(std::string message);

private: 
    // Threshold for logger
    size_t mLevel; 

    std::string mFormat;  
    std::string mPath;

protected: 
    std::ofstream logStream;

    // Used to format message passed in log functions
    std::string formatMessage(std::string message);
    std::string getDate	     (std::string format = "DD/MM/YYYY - hh:mm:ss");
    void replace	     (std::string &str, std::string substr,\
			      std::string replacement);

};

#endif /* end of include guard: LOGGER_H_H3RB85EA */
