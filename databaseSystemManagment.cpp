#include "databaseSystemManagment.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

DatabaseSystemManagment::DatabaseSystemManagment(std::string filepath)
    : Crypto(128){
    mPath = filepath;
}

DatabaseSystemManagment::DatabaseSystemManagment(std::string filepath, std::string key)
    : Crypto(key){
    mPath = filepath;
}

void DatabaseSystemManagment::readFromFile(){
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
	mTable.push_back(record);
	record.clear();
    } 
}
