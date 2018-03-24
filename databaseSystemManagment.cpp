#include "databaseSystemManagment.h"
#include "boost/variant.hpp"

#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<map>

DatabaseSystemManagment::DatabaseSystemManagment(std::string filepath){
    mPath = filepath;
}

std::string DatabaseSystemManagment::substring(std::string str, char separator){
    str.substr(str.find(separator, 0) + 1, 
	       str.find(separator, 0) - str.find(separator, str.find(separator, 0)) - 1);
}

void DatabaseSystemManagment::readFromFile(){
    std::ifstream inputFile(mPath);  
    
    std::map< std::string, boost::variant< std::string, 
	      size_t, double, bool> > record;
    
    std::vector< std::map< std::string, boost::variant< std::string, 
	         size_t, double, bool> > > table;
    
    size_t startPos, endPos;
    bool appendTable = false;
    std::string field, tableName;
    std::vector<std::string> fields;

    for(std::string row; std::getline(inputFile, row);){
	
	if(row.substr(0, 2) == "::"){
	    tableName = row.substr(2, row.length() - 2);
	    table.clear();
	    appendTable = true;
	    row.erase(0, row.length());
	} 

	if(row.substr(0, 2) == ";;"){
	    fields.clear();
	    while(!row.empty()){
		startPos = row.find("\"");
		endPos   = row.find("\"", startPos + 1);
		fields.push_back(row.substr(startPos + 1, endPos - startPos - 1));
		row.erase(0, endPos + 1);
	    }
	}	

	record.clear();
	int i = 0;
	while(!row.empty()){
	    startPos = row.find("\"");
	    endPos   = row.find("\"", startPos + 1);
	    record[fields[i]] = row.substr(startPos + 1, endPos - startPos - 1);
	    row.erase(0, endPos + 1);
	    i++;
	}	
	
	table.push_back(record);		

	if(appendTable) {mTables[tableName] = table; appendTable = false;}
    }

mTables[tableName] = table;
	for(auto Table: mTables)
	for(auto Record: Table.second)
	    for(auto attribute: Record)
		std::cout << "Key: " << Table.first << std::endl << "Key:" << attribute.first << std::endl << attribute.second << std::endl;

}
