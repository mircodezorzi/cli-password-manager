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

std::string DatabaseSystemManagment::substring(std::string str, char separator){
    str.substr(str.find(separator, 0) + 1, 
	       str.find(separator, 0) - str.find(separator, str.find(separator, 0)) - 1);
}

size_t DatabaseSystemManagment::findSecond(std::string str, char character){
    return str.find(character, str.find(character) + 1);
}

void DatabaseSystemManagment::readFromFile(){
    std::ifstream inputFile(mPath);  
    Record record;
    
    size_t startPos, endPos;
    
    // Not a really elegant function but this was the best way I could read data 
    // to a vector of structs
    for(std::string row; std::getline(inputFile, row);){
	record.website = substring(row, '\\');
	row.erase(0, findSecond(row, '\\' ));

	startPos = row.find("\\", endPos);
	endPos   = row.find("\\", startPos + 1);
	record.username = row.substr(startPos + 1, endPos - startPos - 1);
	row.erase(0, endPos + 1);
    } 



    /*
    for(std::string fieldData; std::getline(inputFile, fieldData);){
	while(!fieldData.empty()){
	    startPos = fieldData.find("\"");
	    endPos   = fieldData.find("\"", startPos + 1);
	    field.push_back(fieldData.substr(startPos + 1, endPos - startPos - 1));
	    fieldData.erase(0, endPos + 1);
	}
	mTable.push_back(record);
    }*/

}
