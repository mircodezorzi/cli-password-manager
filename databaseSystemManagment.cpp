#include "databaseSystemManagment.h"
#include "boost/variant.hpp"

#include<vector>
#include<string>
#include<map>
#include<fstream>
#include<math.h>
#include<algorithm>

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

void DatabaseSystemManagment::removeSpaces(std::string &str){
    while(str.find(" ") == 0 || str.find(";") == 0)
	str.erase(0, 1);
}

#include<iostream>
void DatabaseSystemManagment::import(){ 
    // This is probably the most contorted function I've written in this program.
    // The gist of it is that it checks line by line the data file;
    // - if the line starts with a :: then that line will have to contain the table name
    // - if the line starts with a ;; then that line will have to contain the name of the fields
    //	      if before a field name there's a "!" eg: !"username" than that field will become
    //	      the primary key. Otherwise the program will automatically generate progressive IDs.
    //	      The primary key or ID will be stored in a separate table that will contain the key and the table name;
    //	      this is mainly to facilitate the sorting of the tables in the later stages.
    //	- if the line starts with -- then the program will save the current table and if the 
    //	  file continues that the program will do too.    
    //	- after that the program will start reading data fromatted a little bit like this: 
    //	    "google.com" "zucc@gmail.com" "123456"
  
			  std::map<std::string,	boost::variant<std::string, size_t, double, bool>> record;
    std::map<std::string, std::map<std::string, boost::variant<std::string, size_t, double, bool>>> table;
	
    std::ifstream inputFile(mPath);  
    std::vector<std::string> fields;
    std::string tableName, primaryKey, id;
    
    for(std::string row; std::getline(inputFile, row);){
	if(row.substr(0, 2) == "::")			// table name
	    tableName = substring(row, "\"");
	else if(row.substr(0, 2) == ";;"){	        // fields
	    primaryKey = "";
	    fields.clear();
	    while(!row.empty()){
		removeSpaces(row);
		if(row.substr(0, 1) == "!"){		// primary key
		    primaryKey = substring(row, "\"");
		    mPrimaryKeys[tableName] = primaryKey; 
		}
		fields.push_back(substring(row, "\""));	
		row.erase(0, find(row, "\"", 2) + 1);
	    }
	}else if(row.substr(0, 2) == "--"){		// table end	
	    //mTables["data"] = table;
	    table.clear();
	}else{		    				// data
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
}

auto DatabaseSystemManagment::sort(std::string tableName, std::string field){
    std::vector<boost::variant<std::string, size_t, double, bool>> sortedTable;
    for(auto table: mTables){
	if(table.first == tableName){
	    //TODO finish
	}
    }
}

auto DatabaseSystemManagment::query(std::string table, std::vector<std::string> fields){
    // TODO finish
}
