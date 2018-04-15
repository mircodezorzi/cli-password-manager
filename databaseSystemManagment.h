#ifndef DATABASESYSTEMMANAGMENT_H_4WMQHENX
#define DATABASESYSTEMMANAGMENT_H_4WMQHENX

#include "boost/variant.hpp"

#include<vector>
#include<string>
#include<map>

class DatabaseSystemManagment{

public:
    DatabaseSystemManagment(std::string filepath);

    void setPath(std::string p)	    {mPath = p;}

    std::string getPath()	    {return mPath;}
     
    void import();
    
    auto query()		    {return mTables;}
    auto query(std::string table, std::vector<std::string> fields);
    
    auto sort(std::string tableName, std::string fields);

private:
    std::map<std::string, std::map<std::string, std::map<std::string, 
	     boost::variant<std::string, size_t, double, bool>>>> mTables;
    std::map<std::string, std::string> mPrimaryKeys;

protected:
    std::string substring(std::string str, const char *separator);
    size_t	find(std::string str, const char *c, size_t ordinal);	
    void	removeSpaces(std::string &str);

    std::string mPath;
};

#endif /* end of include guard: DATABASESYSTEMMANAGMENT_H_4WMQHENX */
