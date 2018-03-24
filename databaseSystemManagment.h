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
     
    void readFromFile();

private:

protected:
    // refere to single table by string
    // refere to records by index
    // refere to attribute by string
    // eg: 
    //	    mTabels['mainTable'][8]['username']
    // In table mTables get table named mainTable, 8th record and attribute named username
    std::map< std::string, std::vector< std::map< std::string, 
	      boost::variant< std::string, size_t, double, bool> > > > mTables;
   
    std::string substring(std::string str, char separator);

    std::string mPath;
};

#endif /* end of include guard: DATABASESYSTEMMANAGMENT_H_4WMQHENX */
