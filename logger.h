#ifndef LOGGER_H_H3RB85EA
#define LOGGER_H_H3RB85EA

#include <fstream>

#define debugLevel    1
#define infoLevel     2
#define warningLevel  3
#define errorLevel    4
#define criticalLevel 5

class Logger{

public:
    Logger(std::string filepath, size_t threshold = 0, \
	   std::string format = "%(date) - %(time) | level: %(level) | %(msg)");
    
    void setThreshold(size_t t)		{mThreshold = t;}
    void setFormat(std::string f)	{mFormat    = f;}
    void setPath  (std::string p)	{mPath      = p;}
	
    size_t	getThreshold() const	{return mThreshold;}
    std::string getFormat() const       {return mFormat;}
    std::string getPath() const		{return mPath;}

    void log(size_t level, std::string message); 
    void debug	 (std::string message);
    void info	 (std::string message);
    void warning (std::string message);
    void error	 (std::string message);
    void critical(std::string message);
    
    std::string insertLineNumber(std::string str, size_t n);

private: 
    size_t	mThreshold; 
    std::string mFormat;  
    std::string mPath;    

protected: 
    std::ofstream logStream;
    
    std::string formatMessage(std::string message, std::string level);
    std::string getDate	     (std::string format = "DD/MM/YYYY - hh:mm:ss");
    void replace	     (std::string &str, std::string substr,\
			      std::string replacement);
};

#endif /* end of include guard: LOGGER_H_H3RB85EA */
