#ifndef RECORD_H_0OKRQ9WS
#define RECORD_H_0OKRQ9WS

#include "boost/variant.hpp"
#include "../logger.h"

#include<string>
#include<vector>
#include<variant>

class Record : public Logger{
public:
    Record();
   
    auto operator[](std::string index);
	
    void pushBack(std::string index,\
	          boost::variant<std::string, int, double, bool> value);
    
private:
    std::vector< std::string >			mIndicies;
    std::vector< boost::variant<std::string,\
		 int, double, bool > >		mData;
	
protected:

};

#endif /* end of include guard: RECORD_H_0OKRQ9WS */
