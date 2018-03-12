#include "manager.h"
#include "logger.h"

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
    , Crypto(10){
    mPath = dataFilepath;
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

void Manager::appendData(std::string website, std::string username, std::string password){
    std::vector<std::string> temp;
    temp.push_back("\"" + website + "\" ");
    temp.push_back("\"" + username + "\" " );
    temp.push_back("\'" + password + "\"; ");
    mData.push_back(temp);
}

void Manager::readData(){
    std::ifstream inputFile(mPath); 
   
    std::string fieldData;
    std::vector<std::string> record;
    size_t startPos, endPos;
    
    for(std::string fieldData; std::getline(inputFile, fieldData);){
	while(!fieldData.empty()){
	    startPos = fieldData.find("\"");
	    endPos   = fieldData.find("\"", startPos + 1);
	    record.push_back(fieldData.substr(startPos + 1, endPos - startPos - 1));
	    fieldData.erase(0, endPos + 1);
	}
	mData.push_back(record);
	record.clear();
    }   
}
