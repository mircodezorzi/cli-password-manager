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
    }catch()
	critical(errorClipboard);
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
    
    debug(generatingPassword);
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
    size_t sitePos[2], userPos[2], passPos[2], endPos;
    std::vector<std::string> rowData;
    std::string decryptedData;
     
    std::ifstream inputFile(mPath); 
    std::string encryptedData ((std::istreambuf_iterator<char>(inputFile)),\
				std::istreambuf_iterator<char>());
    


    encrypt(encryptedData);
    
    decryptedData = encryptedData;

    do{
	sitePos[0] = decryptedData.find("\"");
	sitePos[1] = decryptedData.find("\"", sitePos[0] + 1);

	userPos[0] = decryptedData.find("\"", sitePos[1] + 1);
	userPos[1] = decryptedData.find("\"", userPos[0] + 1); 
    
	passPos[0] = decryptedData.find("\"", userPos[1] + 1);	
	passPos[1] = decryptedData.find("\"", passPos[0] + 1);
    
	endPos = decryptedData.find(";");

	rowData.push_back(decryptedData.substr(sitePos[0] + 1, sitePos[1] - sitePos[0] - 1));
	rowData.push_back(decryptedData.substr(userPos[0] + 1, userPos[1] - userPos[0] - 1));
	rowData.push_back(decryptedData.substr(passPos[0] + 1, passPos[1] - passPos[0] - 1));
	mData.push_back(rowData);
	
    	rowData.clear();
	decryptedData.erase(0, endPos + 1);
	    


    }while(!decryptedData.empty());
}

void Manager::writeData(){
    /*std::ofstream outputFile(mPath);
    for(std::vector<std::string> i : mData){
	for(std::string j : i){
	    decryptedData += "\"" + j + "\" ";
	}
	decryptedData += "; ";
    }*/
}
