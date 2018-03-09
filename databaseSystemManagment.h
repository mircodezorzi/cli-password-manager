#ifndef DATABASESYSTEMMANAGMENT_H_4WMQHENX
#define DATABASESYSTEMMANAGMENT_H_4WMQHENX

#include <vector>
#include <string>

class DatabaseSystemManagment : public Crypto{

public:
    DatabaseSystemManagment(std::string filepath);
    DatabaseSystemManagment(std::string filepath, std::string key);
	
    void setPath(std::string p)	    {mPath = p;}

    std::string getPath()	    {return mPath;}
    
    // Basic operations
    void	removeRecord (size_t record);
    std::string requestRecord(size_t record);
    std::string appendRecord (std::vector<std::vector<std::string> >); 
    
    void	removeField (size_t field);
    std::string requestField(size_t field);
    std::string appendField (std::vector< std::vector<std::string> >); 

    void readFromFile();

private:

protected:
    std::vector< std::vector<std::string> > mTable;
    
    std::string mPath;
};

#endif /* end of include guard: DATABASESYSTEMMANAGMENT_H_4WMQHENX */
