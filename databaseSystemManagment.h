#ifndef DATABASESYSTEMMANAGMENT_H_4WMQHENX
#define DATABASESYSTEMMANAGMENT_H_4WMQHENX

#include "crypto.h"

#include <vector>
#include <string>

struct Record{
    //std::vector<char> website, username, password, date;
    std::string website, username, password, date;
    bool isFavorite, isReadOnly;    
};


class DatabaseSystemManagment : public Crypto {

public:
    DatabaseSystemManagment(std::string filepath);
    DatabaseSystemManagment(std::string filepath, std::string key);
	
    void setPath(std::string p)	    {mPath = p;}

    std::string getPath()	    {return mPath;}
     
    void readFromFile();

private:

protected:
    std::vector<Record> mTable;
    
    std::string substring(std::string str, char separator);
    size_t findSecond(std::string str, char charater);
    std::string mPath;
};

#endif /* end of include guard: DATABASESYSTEMMANAGMENT_H_4WMQHENX */
