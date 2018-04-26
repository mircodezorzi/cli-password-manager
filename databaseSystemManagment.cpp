#include "databaseSystemManagment.h"

#include "boost/variant.hpp"

#include<vector>
#include<string>
#include<map>

#include<fstream>
#include<algorithm>
#include<math.h>

DatabaseSystemManagment::DatabaseSystemManagment(std::string filepath)\
    : Logger("log", 4){    
    mPath = filepath;
}

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

void DatabaseSystemManagment::import(){ 
    // TODO:
    //	    - add automatic counter if not present in file
    // BUGS:  
    //	    - multiple keys are not supported
    //	    - attributes cannot contain double quotes
    //	    - table name cannot be "data"

			  std::map<std::string,	boost::variant<std::string, size_t, double, bool>> record;
    std::map<std::string, std::map<std::string, boost::variant<std::string, size_t, double, bool>>> table;
	
    std::ifstream inputFile(mPath);  
    std::vector<std::string> fields;
    std::string tableName, primaryKey, id;
    
    try{
	for(std::string row; std::getline(inputFile, row);){
	    if(row.substr(0, 2) == "::")     	 // table name
		tableName = substring(row, "\"");
	    else if(row.substr(0, 2) == ";;"){	 // fields
		primaryKey = "";
		fields.clear();
		while(!row.empty()){
		    removeSpaces(row);
		    if(row.substr(0, 1) == "!"){ // primary key
			primaryKey = substring(row, "\"");
			mPrimaryKeys[tableName] = primaryKey; 
		    }
		    fields.push_back(substring(row, "\""));	
		    row.erase(0, find(row, "\"", 2) + 1);
		}
	    }else if(row.substr(0, 2) == "--"){	// table end	
		mTables[tableName] = table;
		table.clear();
	    }else{		    		// data
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
	}
    }catch(...){
	critical("Error importing database");
	throw std::runtime_error("Error importing database");
    }
}

std::map<std::string, boost::variant<std::string, size_t, double, bool>> DatabaseSystemManagment::query(std::string tableName, std::string recordKey){
    for(auto table: mTables)
	for(auto record: table.second)
	    if(record.first == recordKey)
		return record.second;
}
