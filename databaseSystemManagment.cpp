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

bool DatabaseSystemManagment::import(){
    std::ifstream inputFile(mPath);  
    
    std::map< std::string, boost::variant< std::string, 
	      size_t, double, bool> > record;
    
    std::vector< std::map< std::string, boost::variant< std::string, 
	         size_t, double, bool> > > table;
   
    std::vector<std::string> fields;
    std::string tableName;
    bool tableEnd = false;

    for(std::string row; std::getline(inputFile, row);){
	
	// Set table name
	if(row.substr(0, 2) == "::"){
	    tableName = row.substr(2, row.length() - 2);
	    row.erase(0, row.length());
	} 
	
	// Set attribute names
	else if(row.substr(0, 2) == ";;"){
	    fields.clear();
	    while(!row.empty()){
		fields.push_back(substring(row, "\""));
		row.erase(0, find(row, "\"", 2) + 1);
	    }
	}	
	
	// Set table end
	else if(row.substr(0, 2) == "--")
	    tableEnd = true;
	
	// Read data from line
	else{
	    record.clear();
	    for(int i = 0; i < fields.size(); i++){
		record[fields[i]] = substring(row, "\"");
		row.erase(0, find(row, "\"", 2) + 1);	
	    }	
	    table.push_back(record);		
	}

	// Append table to table array
	if(tableEnd){
	    mTables[tableName] = table;
	    tableEnd = false;
	}
    }
    return true;
}
