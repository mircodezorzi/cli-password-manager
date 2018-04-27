#include "databaseSystemManagment.h"
#include "exceptions.h"

#include "boost/variant.hpp"

#include<vector>
#include<string>
#include<map>

#include<fstream>
#include<algorithm>
#include<math.h>
#include<time.h>

DatabaseSystemManagment::DatabaseSystemManagment()\
    : Logger("log", 0){}

std::string DatabaseSystemManagment::substring(std::string str, const char *separator){
    return str.substr(str.find(separator) + 1,\
		      str.find(separator, str.find(separator) + 1) -\
		      str.find(separator) - 1);
}

size_t DatabaseSystemManagment::find(std::string str, const char *c, size_t ordinal){
    size_t pos = -1;
    for(size_t i = 0; i < ordinal; i++)
	pos = str.find(c, pos + 1);
    return pos;
}

void DatabaseSystemManagment::removeSpaces(std::string &str){
    while(str.find(" ") == 0 || str.find(";") == 0)
	str.erase(0, 1);
}

std::string DatabaseSystemManagment::multiply(char c, size_t n){
    std::string result = "";
    for(size_t i = 0; i < n; i++)
	result += c;
    return result;
}

void DatabaseSystemManagment::import(std::string filepath){ 
    // NOTES:
    //	    - multiple keys are not supported
    //	    - attributes cannot contain double quotes
    //	    - currently all variables are stored as strings
    //	    - table name cannot be "data"
    //
    // TODO:
    //	    - if table name is not present, automatically set it to default value, then automatically
    //	      increment it if there's more than one table
    //	    - add automatic id if not present 
    //	    - finish adding all logging / fail-safes
			  
			  std::map<std::string, boost::variant<std::string, size_t, double, bool>> record;
    std::map<std::string, std::map<std::string, boost::variant<std::string, size_t, double, bool>>> table;
	
    std::ifstream inputFile(filepath);  
    std::vector<std::string> fields;
    std::string tableName = "", primaryKey, id; 
    
    size_t lineIndex = 1,
	   t	     = clock();

    bool keySet = false;

    for(std::string row; std::getline(inputFile, row);){
	if(row.substr(0, 2) == "::")     	 // table name
	    tableName = substring(row, "\"");
	else if(row.substr(0, 2) == ";;"){	 // fields
	    primaryKey = "";
	    fields.clear();
	    while(!row.empty()){
		removeSpaces(row);
		if(row.substr(0, 1) == "!"){	// primary key	
		    if(keySet){
			error(insertLineNumber(primaryKeyOverload, lineIndex));
			throw std::runtime_error(insertLineNumber(primaryKeyOverload, lineIndex));
		    }else{
			primaryKey = substring(row, "\"");
			mPrimaryKeys[tableName] = primaryKey;
			keySet = true;
		    }
		}
		fields.push_back(substring(row, "\""));	
		row.erase(0, find(row, "\"", 2) + 1);
	    }
	}else if(row.substr(0, 2) == "--"){	// table end	
	    mTables[tableName] = table;
	    table.clear();
	}else{					// data
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
	
	if(tableName == ""){
	    error(insertLineNumber(tableNameNotSet, lineIndex));
	    throw std::runtime_error(insertLineNumber(tableNameNotSet, lineIndex));
	}

	lineIndex++;
    }
    
    info("imported database in " + std::to_string(clock() - t) + " ms");
}

std::map<std::string, boost::variant<std::string, size_t, double, bool>> DatabaseSystemManagment::query(std::string tableName, std::string recordKey){
    for(auto table: mTables)
	for(auto record: table.second)
	    if(record.first == recordKey)
		return record.second;
}
