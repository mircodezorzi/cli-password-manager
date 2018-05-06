#ifndef DATABASESYSTEMMANAGMENT_H_4WMQHENX
#define DATABASESYSTEMMANAGMENT_H_4WMQHENX

#include "utilities.h"
#include "logger.h"

#include "boost/variant.hpp"

#include<vector>
#include<string>
#include<map>

#define tbls std::map<std::string, std::map<std::string,std::map<std::string,boost::variant<std::string,size_t,double,bool>>>>
#define tbl  std::map<std::string,std::map<std::string,boost::variant<std::string,size_t,double,bool>>>
#define rcd  std::map<std::string,boost::variant<std::string,size_t,double,bool>>

class DatabaseManagementSystem : private Logger{

public:
    DatabaseManagementSystem();
     
    void import(std::string filepath);
    tbls query() {return mTables;}
    
    rcd query(std::string tableName, std::string recordKey);

private:
    tbls mTables;
    std::map<std::string, std::string> mPrimaryKeys;

protected:
};

#endif /* end of include guard: DATABASESYSTEMMANAGMENT_H_4WMQHENX */
