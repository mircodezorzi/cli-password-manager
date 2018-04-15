#ifndef DISPLAYMANAGER_H_T7LB1KZ4
#define DISPLAYMANAGER_H_T7LB1KZ4

#include "boost/variant.hpp" 

#include<ncurses.h>
#include<string>
#include<vector>
#include<map>
 
enum Align{Center, Left, Right};

class WindowSize{
public:
    WindowSize operator=(WindowSize other){
        w = other.w;
        h = other.h;
    }

    size_t w, h;
};
 
class DisplayManager{ 

public:
    DisplayManager();
    ~DisplayManager();

    void checkForWindowResize();
    void printFrame();
    void resetCursor();
    
    // TODO add attribute parameter
    void print(std::string str, size_t row, Align a); 
    void printLine(size_t row);
    void printFile(std::string path);
    void printTable(std::map<std::string, std::map<std::string,\
	            boost::variant<std::string, size_t, double, bool>>> table); 

private:  
    WindowSize getWindowSize();

    WINDOW    *mWindow;
    WindowSize mWindowsize;
    
protected:

};



#endif /* end of include guard: DISPLAYMANAGER_H_T7LB1KZ4 */
