#include "manager.h"
#include "logger.h"

#include "exceptions.h"

#include <fstream>
#include <streambuf>
#include <string>

// TODO for debug porpuses, con be removed when class is finished
#include <iostream>

Manager::Manager(std::string dataFilepath, std::string logFilpath, size_t logThresholdLevel, std::string LogMessageFormat) 
    :Logger(logFilpath, logThresholdLevel, LogMessageFormat){

    mPath = dataFilepath;
}

void Manager::readData(){
    size_t sitePos[2], userPos[2], passPos[2], endPos;
    std::vector<std::string> rowData;
    
    std::ifstream inputFile(mPath); 
    std::string encryptedData ((std::istreambuf_iterator<char>(inputFile)),\
				std::istreambuf_iterator<char>());
    
    std::cout << encryptedData;
    mDecryptedData = encryptedData;
    
    do{
	sitePos[0] = mDecryptedData.find("\"");
	sitePos[1] = mDecryptedData.find("\"", sitePos[0] + 1);

	userPos[0] = mDecryptedData.find("\"", sitePos[1] + 1);
	userPos[1] = mDecryptedData.find("\"", userPos[0] + 1); 
    
	passPos[0] = mDecryptedData.find("\"", userPos[1] + 1);	
	passPos[1] = mDecryptedData.find("\"", passPos[0] + 1);
    
	endPos = mDecryptedData.find(";");

	rowData.push_back(mDecryptedData.substr(sitePos[0] + 1, sitePos[1] - sitePos[0] - 1));
	rowData.push_back(mDecryptedData.substr(userPos[0] + 1, userPos[1] - userPos[0] - 1));
	rowData.push_back(mDecryptedData.substr(passPos[0] + 1, passPos[1] - passPos[0] - 1));
	mData.push_back(rowData);
	
    	rowData.clear();
	mDecryptedData.erase(0, endPos + 1);

    }while(!mDecryptedData.empty());

    info();
    // prints out the mData array, can be deleted
    for(std::vector<std::string> i : mData){
	for(std::string j : i)
	    std::cout << j << " - ";
	std::cout << std::endl;
    }

}

void Manager::writeData(){
    std::ofstream outputFile(mPath);
    for(std::vector<std::string> i : mData){
	for(std::string j : i){
	    mDecryptedData += "\"" + j + "\" ";
	}
	mDecryptedData += "; ";
    }
}
