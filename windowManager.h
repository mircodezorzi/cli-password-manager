#ifndef WINDOWMANAGER_H_NIDXF4BF
#define WINDOWMANAGER_H_NIDXF4BF

#include "boost/variant.hpp" 

#include<ncurses.h>
#include<string>
#include<vector>
#include<map>

#include<sys/ioctl.h>
#include<unistd.h>

struct Vector{
    size_t w,
	   h;
};

enum Align{Center, Left, Right};

class WindowManager{
     
public:
    WindowManager();
    ~WindowManager();

    void checkForWindowResize();

    void printFrame();

    // TODO add attribute parameter
    void print(std::string str, size_t row, Align a);
    
    void printLine(size_t row);
    void printFile(std::string path);

    void printTable(std::vector< std::map< std::string,\
	            boost::variant< std::string, size_t, double, bool> > > table); 

private:
    void resetCursor();
    bool getWindowSize();

    WINDOW *mWindow;
    Vector mWindowsize;
    
protected:

};

#endif /* end of include guard: WINDOWMANAGER_H_NIDXF4BF */
