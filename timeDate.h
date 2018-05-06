#ifndef TIMEDATE_H_XMQJKOJU
#define TIMEDATE_H_XMQJKOJU

#include "databaseManagementSystem.h"

#include<stdlib.h>
#include<fstream>
#include<string>
#include<vector>
#include<map>

namespace TimeDate{

    struct Instant{
	unsigned int year = 0,
		     mon = 0,
		     day = 0,
		     hour = 0,
		     min = 0,
		     sec = 0;
	
	Instant operator=(Instant other);
	Instant operator+(Instant other); 
    };

    class WeekdayDictionary : private DatabaseManagementSystem{
    public:
        WeekdayDictionary(std::string path);
	std::vector<std::string> operator[](std::string language);
    };
    
    Instant	now();
    std::string weekdayName(Instant i);
    std::string instantToString(Instant i, std::string format = "DD/MM/YYYY hh:mm:ss");
     
    /*
    enum Lang{Iano = 0, English  = 1};
    Instant     addTimeDuration(Instant i, Instant d) {return i + d;};
    */	

};
#endif /* end of include guard: TIMEDATE_H_XMQJKOJU */
