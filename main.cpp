//#include <ncurses.h>

//#include "utils.h"
//#include "crypt.h"
//#include "fileStream.h"

//#include "logger.h"
#include "manager.h"
#include "crypto.h"

#include <math.h>
#include <iostream>
#include <vector>

int main(){
    std::string test = "123123123123781292";
    Crypto crypto("generatedKey", 5);
    crypto.encrypt(test);
    //crypto.encrypt(test);
    //std::cout << test;
    //Manager manager;
    //manager.setFilepath("data.crypt");
    //manager.readData();
    //manager.writeData(); 
    //std::cout << fileio::read("data");
    //Logger logger("out.log", 3, "test");
    //logger.log(5, "this is just a test of level 5");
    return 0;
}
