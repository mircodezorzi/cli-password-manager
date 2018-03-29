#include "manager.h"
#include "logger.h"
#include "display.h"

#include "exceptions.h"

#include <fstream>
#include <streambuf>
#include <string>
#include <stdlib.h>
#include <time.h>

// TODO for debug porpuses, con be removed when class is finished
#include <iostream>

Manager::Manager(std::string dataFilepath, std::string logFilpath, size_t logThresholdLevel, std::string logMessageFormat) 
    : Logger(logFilpath, logThresholdLevel, logMessageFormat)
    , Crypto(10), 
    Display(){
    mPath = dataFilepath;
    state = Running;
}

void Manager::start(){
    switch(state){
	case Running:
	    mainLoop();
	    break;
    }
}

void Manager::mainLoop(){
    printFrame(0);
    printBottomFrame();
    printMiddle(0, "cli-password-manager");
    setCursor();
    char input = getInput();
    if(input == 'q') state = Exiting;

}

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
