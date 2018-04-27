#include "programManager.h"

ProgramManager::ProgramManager(std::string dbFilepath)
    : DatabaseSystemManagment()
    , DisplayManager(){
    mDbFilepath = dbFilepath;
}

void ProgramManager::start(){
    mSelected   = 0;    
    mState = Running;
    import(mDbFilepath);
    loop();
}

void ProgramManager::loop(){
    while(mState != Exiting){
	update();
	draw();
	events();
    }
}

void ProgramManager::draw(){
    printFrame();
    switch(mState){
	case Running:
	    printTable(query()["userdata"], mSelected);    
	    break;
    }
}

void ProgramManager::events(){
    switch(checkInput()){	
	case KEY_UP:
	    mSelected--;
	    break;
	case KEY_DOWN:
	    mSelected++;
	    break;
	case KEY_RIGHT:
	    break;
	case KEY_LEFT:
	    break;
	case 'a':
	    //copyToClipboard(boost::get<std::string>(query("userdata", "001")["password"]));
	    break;
	case 'q':
	    mState = Exiting;
	    break;
    } 
}

void ProgramManager::update(){
    checkForWindowResize();
}

/*
void copyToClipboard(std::string s){
    try{
	std::string command = "echo \"" + s + "\" | xsel -b";
	system(command.c_str());
    }catch(int e){
    }
}
*/

/*
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
