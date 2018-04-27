#ifndef PROGRAMMANAGER_H_AKLYD7VY
#define PROGRAMMANAGER_H_AKLYD7VY

#include "databaseSystemManagment.h"
#include "displayManager.h"

class ProgramManager : private DatabaseSystemManagment, private DisplayManager{

public:
    ProgramManager(std::string databasePath);

    void start();

private:
    void loop();
        
    void draw();
    void update();
    void events();	

    enum State{Running, HelpMenu, Exiting};
    
    State mState; 
    size_t mSelected;
    
    std::string mDbFilepath;

    /*  void copyToClipboard(std::string s);
   
    std::string generatePassword(size_t lenght, std::string blacklistedCharacters = "");
    // When generating the password this are the default blacklisted characters
    std::string mBlacklistedCharacters = "{}[]()/\\'\"`~,;:.<>";
    */ 

protected:

};

#endif /* end of include guard: PROGRAMMANAGER_H_AKLYD7VY */
