#ifndef MANAGER_H_FSNLIKSO
#define MANAGER_H_FSNLIKSO

#include "logger.h"
#include "crypto.h"

#include <vector>
#include <string>

class Manager : private Logger, private Crypto{

public:
    Manager(std::string dataFilepath = "data.crypt", std::string logFilepath = "out.log",\
	    size_t logThersholdLevel = 0, std::string logMessageFormat = "%(date) - %(time) - %(level) - %(msg)");
  
    void setFilepath(std::string dataFilepath) {mPath = dataFilepath;}
    void setLogFilpath(std::string logFilepath) {mPath = logFilepath;}

    std::string generatePassword(size_t lenght, std::string blacklistedCharacters = "");
    void appendData(std::string website, std::string username, std::string password);

    void readData();
    void writeData();

private:
    std::vector< std::vector<std::string> > mData;
    
    std::string mBlacklistedCharacters = "{}[]()/\\'\"`~,;:.<>";
    std::string mPath;
};

#endif /* end of include guard: MANAGER_H_FSNLIKSO */
