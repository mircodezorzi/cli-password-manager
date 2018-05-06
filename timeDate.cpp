#include "timeDate.h"
#include "utilities.h"

#include<string>
#include<ctime>

TimeDate::Instant TimeDate::now(){
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    
    Instant i;
    i.year = tm->tm_year + 1900;
    i.mon = tm->tm_mon + 1;
    i.day = tm->tm_mday;
    i.hour = tm->tm_hour;
    i.min = tm->tm_min;
    i.sec= tm->tm_sec;    
    
    return i;
}
 
TimeDate::Instant TimeDate::Instant::operator=(Instant other){
    year = other.year;
    mon = other.mon;
    day = other.day;
    hour = other.hour;
    min = other.min;
    sec = other.sec;
}

TimeDate::Instant TimeDate::Instant::operator+(Instant other){
    year += other.year;
    mon += other.mon;
    day += other.day;
    hour += other.hour;
    min += other.min;
    sec += other.sec;

    if(sec >= 60){
	min += sec / 60;
	sec %= 60;
    }

    if(min >= 60){
	hour += min / 60;
	min %= 60;
    }

    if(hour >= 24){
	day += hour / 24;
	hour %= 24;
    }
    
    while(day >= 31){
	if(day > 28 && mon == 2 && year % 4 != 0 && year % 400 == 0){
	    mon++;
	    day -= 28;
	}else if(day > 29 && mon == 2){
	    mon++;
	    day -= 29;
	}else if(day > 31 && (mon == 1 || mon == 3 || mon == 5 || 
		  mon == 7 || mon == 8 || mon == 10|| mon == 12)){
	    mon++;
	    day -= 31;
	}else{
	    mon++;
	    day -= 30;
	}
    }
    
    if(mon > 12){
	year += mon % 12;
	mon %= 12;
    }

    return *this;
}

TimeDate::WeekdayDict::WeekdayDict(std::string path){
    import(path);
}

std::string TimeDate::instantToString(Instant i, std::string format){
    using namespace utilities;
    replace(format, "YYYY", std::to_string(i.year));
    replace(format, "DD", charIfCondition('0', i.day < 10) + std::to_string(i.day));
    replace(format, "MM", charIfCondition('0', i.mon < 10) + std::to_string(i.mon));
    replace(format, "hh", charIfCondition('0', i.hour < 10) + std::to_string(i.hour));
    replace(format, "mm", charIfCondition('0', i.min < 10) + std::to_string(i.min));
    replace(format, "ss", charIfCondition('0', i.sec < 10) + std::to_string(i.sec));
    
    replace(format, "YY", std::to_string(i.year - i.year / 100 * 100));
    replace(format, "M", std::to_string(i.mon));
    replace(format, "D", std::to_string(i.day));
    replace(format, "h", std::to_string(i.hour));
    replace(format, "m", std::to_string(i.min));
    replace(format, "s", std::to_string(i.sec)); 
    
    return format;
}


std::string Timer::weekdayName(Instant i){
    Lang lang = Italiano;
    WeekdayNameDict dict;
    dict.readFromFile("dictionary");
    
    size_t Y = i.years - 1 * (i.months == 1 || i.months == 2),
	   y = i.years - i.years / 100 * 100,
	   c = (i.years - y) / 100,
	   m = shift(i.months, 10, 12),	
	   w = (size_t)(1 + floor(2.6 * m - 0.2) + y + floor(y / 4) + floor(c / 4) - 2 * c) % 7;
    
    w += 7 * (w < 0);

    return dict[lang][w - 1];
}
