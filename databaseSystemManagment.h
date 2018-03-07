#ifndef DATABASESYSTEMMANAGMENT_H_4WMQHENX
#define DATABASESYSTEMMANAGMENT_H_4WMQHENX

#include <vector>
#include <string>

class DatabaseSystemManagment{
public:
    DatabaseSystemManagment(std::string filepath);
	
    void setPath(std::string p)	    {mPath = p;}

    std::string getPath()	    {return mPath;}
    

    void readTableFromFile();
    
    void sortTable(std::string field);

    void printPrint();

private:

protected:
    std::vector< std::vector<std::string> > mTable;
    
    std::string mPath;
};

#endif /* end of include guard: DATABASESYSTEMMANAGMENT_H_4WMQHENX */
