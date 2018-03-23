#include "record.h"
#include "../logger.h"

auto Record::operator[](std::string index){
    for(int i = 0; i < mIndicies.size(); i++)
	if(mIndicies[i] == index)
	    return mData[i];
}

void Record::pushBack(std::string index,\
		      boost::variant<std::string, int, double, bool> value){
    mIndicies.push_back(index);
    mData.push_back(value);
}
