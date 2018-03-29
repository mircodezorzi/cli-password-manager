#ifndef DISPLAY_H_04PCO5YP
#define DISPLAY_H_04PCO5YP

#include<ncurses.h>
#include<string>

// TODO make program multi-platform, this library is unix-specific
#include<sys/ioctl.h>
#include<unistd.h>

struct Vector{
    size_t x,\
	   y;
};

class Display{

public:	
    Display(); 
    ~Display();

    void printMiddle(size_t y, std::string str);
    void printFrame(size_t y);
    void printBottomFrame();

    void printData();

    void setCursor();
    char getInput();

private:
    WINDOW *mWindow;
    Vector mWindowsize;

};

#endif /* end of include guard: DISPLAY_H_04PCO5YP */
