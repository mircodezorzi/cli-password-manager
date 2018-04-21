#include "displayManager.h"

#include "boost/variant.hpp"

#include <locale.h>
#include<fstream>
#include<ncurses.h>
#include<string>
#include<vector>
#include<variant>
#include<map>

#ifdef __linux__ 
    #include<sys/ioctl.h>
    #include<unistd.h> 
#elif _WIN32 | _WIN64
    #include<windows.h>
#endif

DisplayManager::DisplayManager(){
   if(true){
	mWindow = initscr();	
	setlocale(LC_ALL, "");
	keypad(mWindow, TRUE);
	
	curs_set(0);
	noecho();
	raw();
    }else
	throw std::runtime_error("error reading terminal size");
}

DisplayManager::~DisplayManager(){
    delwin(mWindow);
    endwin();
}

WindowSize DisplayManager::getWindowSize(){
    WindowSize windowsize;
    #ifdef __linux__ 
        struct winsize window;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
        windowsize.w = window.ws_col;
        windowsize.h = window.ws_row;
    #elif _WIN32 | _WIN64
	try{
	    CONSOLE_SCREEN_BUFFER_INFO csbi;
	    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	    windowsize.w = csbi.srWindow.Right - csbi.rsWindow.Left + 1;
	    windowsize.h = csbi.srWindow.Bottom - csbi.rsWindow.Top + 1;
	}catch(...){
	
	}
    #endif
       return windowsize;
}

void DisplayManager::checkForWindowResize(){
    WindowSize newWindowsize;
    newWindowsize = getWindowSize();
    if(newWindowsize.w != mWindowsize.w || newWindowsize.h != newWindowsize.h){
	mWindowsize.w = newWindowsize.w;
	mWindowsize.h = newWindowsize.h;
	clear();
    }
}

int DisplayManager::checkInput(){
    return wgetch(mWindow);
}

void DisplayManager::resetCursor(){
    move(mWindowsize.h - 1, 0);
}

void DisplayManager::drawLine(size_t pos, Direction direction){
    size_t oldPos[2] = {getcurx(mWindow), getcury(mWindow)};
    if(direction == Horizontal){
	move(pos, 0);
         for(int i = 0; i < mWindowsize.w; i++)
 	    addch(ACS_HLINE);
     }else{
 	move(0, pos);
	for(int i = 0; i < mWindowsize.h; i++)
	    addch(ACS_VLINE);  
    }
    move(oldPos[0], oldPos[1]);
}

void DisplayManager::print(std::string str, size_t row, Align a){
    size_t oldPos[2] = {getcurx(mWindow), getcury(mWindow)};
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
    move(oldPos[0], oldPos[1]);
}

void DisplayManager::printFrame(){
    size_t oldPos[2] = {getcurx(mWindow), getcury(mWindow)};
    attron(A_STANDOUT); 
    mvhline(0, 0, ' ', mWindowsize.w);
    mvhline(mWindowsize.h - 1, 0, ' ', mWindowsize.w);
    print("cli-password-manager", 0, Center);
    attroff(A_STANDOUT); 
    resetCursor();
}

void DisplayManager::printFile(std::string path){
    move(0, 0);
    std::ifstream inputFile(path);
    for(std::string line; std::getline(inputFile, line);){
	mvprintw(getcury(mWindow) + 1, 0, line.c_str());
    }
}

void DisplayManager::printLine(size_t row){
    size_t oldPos[2] = {getcurx(mWindow), getcury(mWindow)};
    attron(A_STANDOUT); 
    mvhline(row, 0, ' ', mWindowsize.w);
    attroff(A_STANDOUT);
    move(oldPos[0], oldPos[1]);
}

void DisplayManager::clearRow(size_t row){
    size_t oldPos[2] = {getcurx(mWindow), getcury(mWindow)};
    mvhline(row, 0, ' ', mWindowsize.w);
    move(oldPos[0], oldPos[1]); 
}

void DisplayManager::printTable(std::map<std::string, std::map<std::string, 
	boost::variant<std::string, size_t, double, bool>>> table, size_t selected){
    
    size_t tableRow = 3;
    printLine(tableRow);
    move(tableRow + 1, 0); 
    size_t i = 0;
    size_t colW = mWindowsize.w / table.size(); 
    for(auto record: table){
	for(auto attribute : record.second){ 
	    size_t oldX = getcurx(mWindow);
	    size_t oldY = getcury(mWindow);
	   	    attron(A_STANDOUT);	
 	    mvprintw(tableRow, getcurx(mWindow), attribute.first.c_str());
 	    attroff(A_STANDOUT);  
	  
	    if(i == selected){
		//printLine(i + tableRow + 1);
		attron(A_BOLD);
	    }else
		i = i;
		//clearRow(i + tableRow + 1);
	    move(oldY, oldX);	    
	    printw(boost::get<std::string>(attribute.second).c_str());
	    if(i == selected)
		attroff(A_BOLD);  
	    
	    move(getcury(mWindow), colW);
	    colW += colW;
	    }
	colW = mWindowsize.w / table.size();
	move(getcury(mWindow) + 1, 0);
	i++;
    }

}
