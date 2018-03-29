#include "display.h"
#include "databaseSystemManagment.h"

#include "boost/variant.hpp"

#include<ncurses.h>
#include<string>

#include<iostream>

// TODO make program multi-platform, these two libraries are unix-specific
#include<sys/ioctl.h>
#include<unistd.h>

Display::Display(){
    struct winsize windowsize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &windowsize);

    mWindowsize.x = windowsize.ws_col;
    mWindowsize.y = windowsize.ws_row;
    
    mWindow = initscr();

    noecho();
    raw();
    curs_set(0);
}

Display::~Display(){
    delwin(mWindow);
    endwin();
}

void Display::printMiddle(size_t y, std::string str){
    attron(A_STANDOUT);
    mvprintw(y, mWindowsize.x / 2 - str.length() / 2, str.c_str());
    attroff(A_STANDOUT);
}

void Display::printFrame(size_t y){
    attron(A_STANDOUT);
    mvhline(y, 0, ' ', mWindowsize.x);
    attroff(A_STANDOUT);
}

void Display::printBottomFrame(){
    attron(A_STANDOUT);
    mvhline(mWindowsize.y - 2, 0, ' ', mWindowsize.x);
    attroff(A_STANDOUT);
}

void Display::setCursor(){
    move(mWindowsize.y - 1, 0);
}

char Display::getInput(){
    char input = getch();
    addch(input);
    return input;
}

void Display::printData(){
    DatabaseSystemManagment dsm("data.crypt");
    dsm.import();
    std::map< std::string, std::vector< std::map< std::string, 
	      boost::variant< std::string, size_t, double, bool> > > > mTables = dsm.query();
}
