#ifndef MANAGER_H_FSNLIKSO
#define MANAGER_H_FSNLIKSO

#include "logger.h"
#include "crypto.h"

#include <vector>
#include <string>

class Manager : private Logger, public Crypto{

public:
    Manager(std::string dataFilepath = "data.crypt", std::string logFilepath = "out.log",\
	    size_t logThersholdLevel = 0, std::string LogMessageFormat = "%(date) - %(time) - %(level) - %(msg)");
  
    void setFilepath(std::string dataFilepath) {mPath = dataFilepath;}
    void setLogFilpath(std::string logFilepath) {mPath = logFilepath;}

    void readData();
    void writeData();

private:
    std::vector< std::vector<std::string> > mData;
    std::string mPath;
};

#endif /* end of include guard: MANAGER_H_FSNLIKSO */
