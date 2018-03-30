#include "windowManager.h"

#include "boost/variant.hpp"

#include<fstream>
#include<ncurses.h>
#include<string>
#include<vector>
#include<variant>
#include<map>

WindowManager::WindowManager(){
    if(getWindowSize()){
	mWindow = initscr();
	//start_color();

	raw();
	noecho();
	curs_set(0);
    }else
	throw std::runtime_error("error reading terminal size");
}

WindowManager::~WindowManager(){
    delwin(mWindow);
    endwin();
}

// If there's any error, return false
bool WindowManager::getWindowSize(){
    Vector newWindowsize;
    #ifdef __linux__ 
	try{
	    #include<sys/ioctl.h>
	    #include<unistd.h> 
	    struct winsize windowsize;
	    ioctl(STDOUT_FILENO, TIOCGWINSZ, &windowsize);
	    newWindowsize.w = windowsize.ws_col;
	    newWindowsize.h = windowsize.ws_row;
	}catch(...){
	    return false;
	}
    #elif _WIN32 | _WIN64
	try{
	    #include<windows.h>
	    CONSOLE_SCREEN_BUFFER_INFO csbi;
	    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	    newWindowsize.w = csbi.srWindow.Right - csbi.rsWindow.Left + 1;
	    newWindowsize.h = csbi.srWindow.Bottom - csbi.rsWindow.Top + 1;
	}catch(...){
	    return false;
	}
    #endif
    
    // This function will be called in the update method in programManager
    // if the window is resized then update it's dimensions
    if(newWindowsize.w != mWindowsize.w || newWindowsize.h != newWindowsize.h){
	mWindowsize.w = newWindowsize.w;
	mWindowsize.h = newWindowsize.h;
	clear();
    }
    
    return true;
}


void WindowManager::checkForWindowResize(){
    getWindowSize();
}

void WindowManager::resetCursor(){
    move(mWindowsize.h - 1, 0);
}

void WindowManager::print(std::string str, size_t row, Align a){
    switch(a){
	case Center:
	    mvprintw(row, mWindowsize.w / 2 - str.length() / 2, str.c_str());
	    break;
	case Left:
	    mvprintw(row, 0, str.c_str());
	    break;
	case Right:
	    mvprintw(row, mWindowsize.w - str.length(), str.c_str());
	    break;
    }
}

void WindowManager::printFrame(){
    attron(A_STANDOUT); 
    mvhline(0, 0, ' ', mWindowsize.w);
    mvhline(mWindowsize.h - 1, 0, ' ', mWindowsize.w);
    print("cli-password-manager", 0, Center);
    attroff(A_STANDOUT); 
    resetCursor();
}

void WindowManager::printFile(std::string path){
    move(0, 0);
    std::ifstream inputFile(path);
    for(std::string line; std::getline(inputFile, line);){
	mvprintw(getcury(mWindow) + 1, 0, line.c_str());
    }
}

void WindowManager::printLine(size_t row){
    attron(A_STANDOUT); 
    mvhline(row, 0, ' ', mWindowsize.w);
    attroff(A_STANDOUT); 
}

void WindowManager::printTable(std::vector< std::map < std::string,\
			       boost::variant< std::string, size_t, double, bool > > > table){
    printLine(2);
 
    move(3, 0);
    size_t colW = mWindowsize.w / table[0].size();
    for(auto record : table){
	for(auto attribute : record){
	    size_t oldX = getcurx(mWindow);
	    size_t oldY = getcury(mWindow);
	    attron(A_STANDOUT);	
	    mvprintw(2, getcurx(mWindow), attribute.first.c_str());
	    attroff(A_STANDOUT);  
	    move(oldY, oldX);
	    printw(boost::get<std::string>(attribute.second).c_str());
	    move(getcury(mWindow), colW);
	    colW += colW;
	}
	colW = mWindowsize.w / table[0].size();
	move(getcury(mWindow) + 1, 0);
    }
}
