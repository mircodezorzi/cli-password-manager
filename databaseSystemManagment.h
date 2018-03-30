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
     
    bool import();
    auto query()		    {return mTables;}
    auto query(std::string field);

private:
    // to access an element: 
    //	    mTabels['mainTable'][8]['username']
   
    std::map< std::string, std::vector< std::map< std::string, 
	      boost::variant< std::string, size_t, double, bool> > > > mTables;
    
protected:
    std::string substring(std::string str, const char *separator);
    size_t find(std::string str, const char *c, size_t ordinal);	

    std::string mPath;
};

#endif /* end of include guard: DATABASESYSTEMMANAGMENT_H_4WMQHENX */
