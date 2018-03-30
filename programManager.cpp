#include "programManager.h"

ProgramManager::ProgramManager(std::string dbPath)\
    : DatabaseSystemManagment(dbPath)\
    , WindowManager(){
}

void ProgramManager::start(){
    mState = Running;
    import();
    mainLoop();
}

void ProgramManager::mainLoop(){
    while(mState != Exiting){
	draw();
	events();
	update();
    }
}

void ProgramManager::draw(){
    printFrame();
    switch(mState){
	case Running:
	    printTable(query()["data"]);    
	    break;
	case HelpMenu:
	    // TODO add help menu
	    break;
    }
}

void ProgramManager::events(){
    if(getch() == 'q') mState = Exiting; 
}

void ProgramManager::update(){
    checkForWindowResize();
}

/*
void Manager::copyToClipboard(std::string s){
    try{
	std::string command = "echo \"" + s + "\" | xsel -b";
	system(command.c_str());
    }catch(int e){
    }
}


std::string Manager::generatePassword(size_t lenght, std::string blacklistedCharacters){ 
    blacklistedCharacters += mBlacklistedCharacters;
    std::string password, randomCharacter;
    
    for(int i = 0; i < lenght; i++){
	randomCharacter = (char) (rand() % 93) + 34;
	if(randomCharacter.find_first_of(blacklistedCharacters) != -1)
	    password += randomCharacter;
	else
	    i--;
    }
    
    //debug(generatingPassword);
    return password;
}
*/