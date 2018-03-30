#ifndef PROGRAMMANAGER_H_AKLYD7VY
#define PROGRAMMANAGER_H_AKLYD7VY

#include "databaseSystemManagment.h"
#include "windowManager.h"

class ProgramManager : private DatabaseSystemManagment, private WindowManager{

public:
    ProgramManager(std::string dbPath);
    void start();

private:
    void mainLoop();
    
    void draw();
    void update();
    void events();	
/*  void copyToClipboard(std::string s);
   
    std::string generatePassword(size_t lenght, std::string blacklistedCharacters = "");
    // When generating the password this are the default blacklisted characters
    std::string mBlacklistedCharacters = "{}[]()/\\'\"`~,;:.<>";
 */   
    enum State{Running, HelpMenu, Exiting};
    State mState;

protected:


};

#endif /* end of include guard: PROGRAMMANAGER_H_AKLYD7VY */
