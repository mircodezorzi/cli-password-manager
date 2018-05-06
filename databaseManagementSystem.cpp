#include "databaseManagementSystem.h"
#include "exceptions.h"

#include "boost/variant.hpp"

#include<vector>
#include<string>
#include<map>

#include<fstream>
#include<algorithm>
#include<math.h>
#include<time.h>

DatabaseManagementSystem::DatabaseManagementSystem()\
    : Logger("log", 0){}

void DatabaseManagementSystem::import(std::string filepath){ 
    // NOTES:
    //	    - attributes cannot contain double quotes
    //	    - currently all variables are stored as strings
    //	    - table name cannot be "data"
    //
    // TODO:
    //	    - if table name is not present, automatically set it to default value, then automatically
    //	      increment it if there's more than one table
    //	    - add automatic id if not present 
    //	    - finish adding all logging / fail-safes
			  

    // TODO clear variable declaration
    std::ifstream inputFile(filepath);  
    std::vector<std::string> fields;
    std::string tableName = "", primaryKey, id;  
    size_t lineIndex = 1,
	   tableNumber = 0,
	   t	     = clock();
    bool keySet = false;
    //

    using namespace utilities;
    rcd record;
    tbl table;
    
    for(std::string row; std::getline(inputFile, row);){
	if(row.substr(0, 2) == "::"){
	    if(!containsCharacters(row, '"', 2)){
		warning(insertLineNumber(missingDoubleQuotes, lineIndex));
		row += '"';
		tableName = substring(row, "\"");    
	    }
	    try{
		tableName = substring(row, "\"");
	    }catch(...){
		warning(insertLineNumber(tableNameNotSet, lineIndex));
		tableName = "table" + std::to_string(tableNumber);
		tableNumber++;
	    }
	}else if(row.substr(0, 2) == ";;"){
	    if(tableName == ""){
		warning(insertLineNumber(tableNameNotSet, lineIndex));
		tableName = "table" + std::to_string(tableNumber);
		tableNumber++; 
	    }
	    primaryKey = "";
	    fields.clear();
	    while(!row.empty()){
		removeSpacesUntill(row, ';');
		if(row.substr(0, 1) == "!"){
		    if(keySet){
			warning(insertLineNumber(primaryKeyOverload, lineIndex));
		    }else{
			primaryKey = substring(row, "\"");	
			mPrimaryKeys[tableName] = primaryKey;
			keySet = true;
		    }
		}
		fields.push_back(substring(row, "\""));	
		row.erase(0, find(row, "\"", 2) + 1);
	    }
	}else if(row.substr(0, 2) == "--"){	
	    if(tableName == ""){
		warning(insertLineNumber(tableNameNotSet, lineIndex));
		tableName = "table" + std::to_string(tableNumber);
		tableNumber++; 
	    }
	    mTables[tableName] = table;
	    table.clear();
	}else{
	////////////////////////
	// TODO finish debugging
	////////////////////////
	    record.clear();
	    for(int i = 0; i < fields.size(); i++){
		if(fields[i] == primaryKey)
		    id =  substring(row, "\"");
		else
		    record[fields[i]] = substring(row, "\"");
		row.erase(0, find(row, "\"", 2) + 1);	
	    }
	    table[id] = record;
	}
	lineIndex++;
    }
    
    info("imported database in " + std::to_string(clock() - t) + " ms");
}

rcd DatabaseManagementSystem::query(std::string tableName, std::string recordKey){
    for(auto table: mTables)
	for(auto record: table.second)
	    if(record.first == recordKey)
		return record.second;
}
