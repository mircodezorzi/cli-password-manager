#ifndef MANAGER_H_FSNLIKSO
#define MANAGER_H_FSNLIKSO

#include "logger.h"
#include "crypto.h"
#include "display.h"

#include <vector>
#include <string>

class Manager : private Logger, private Crypto, private Display{

public:
    Manager(std::string dataFilepath = "data.crypt", std::string logFilepath = "out.log",\
	    size_t logThersholdLevel = 0, std::string logMessageFormat = "%(date) - %(time) - %(level) - %(msg)");

    void setFilepath(std::string dataFilepath) {mPath = dataFilepath;}
    void setLogFilpath(std::string logFilepath) {mPath = logFilepath;}

    std::string generatePassword(size_t lenght, std::string blacklistedCharacters = "");
    void appendData(std::string website, std::string username, std::string password);

    void start();

private:

    void mainLoop();

    enum State {Running, HelpMenu, Exiting};
    State state;

    void copyToClipboard(std::string s);
   
    // When generating the password this are the default blacklisted characters
    std::string mBlacklistedCharacters = "{}[]()/\\'\"`~,;:.<>";
    
    std::string mPath;

};

#endif /* end of include guard: MANAGER_H_FSNLIKSO */
