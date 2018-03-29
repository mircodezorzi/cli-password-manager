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

std::string DatabaseSystemManagment::substring(std::string str, const char *separator){
    return str.substr(str.find(separator) + 1,\
		      str.find(separator, str.find(separator) + 1) -\
		      str.find(separator) - 1);
}

size_t DatabaseSystemManagment::find(std::string str, const char *c, size_t ordinal){
    size_t pos = -1;
    for(int i = 0; i < ordinal; i++)
	pos = str.find(c, pos + 1);
    return pos;
}

void DatabaseSystemManagment::import(){
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
		fields.push_back(substring(row, "\""));
		row.erase(0, find(row, "\"", 2) + 1);
	    }
	}	
	
	record.clear();
	int i = 0;
	while(!row.empty()){
	    record[fields[i]] = substring(row, "\"");
	    row.erase(0, find(row, "\"", 2) + 1);
	    i++;
	}	
	
	table.push_back(record);		

	if(appendTable) {mTables[tableName] = table; appendTable = false;}
    }
    
    mTables[tableName] = table;
    mTables.erase("");
}
