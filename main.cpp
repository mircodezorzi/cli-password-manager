//#include <ncurses.h>

//#include "utils.h"
//#include "crypt.h"
//#include "fileStream.h"

#include "utils.h"

//#include "logger.h"
#include "manager.h"
#include "crypto.h"

#include <math.h>
#include <iostream>
#include <vector>

int main(){
    std::vector<bool> test;

    std::cout utils::toHex(test);

    /*
    std::string test = "123";
    Crypto crypto("ABC");
    std::cout << test << std::endl;
    crypto.encrypt(test);
    std::cout << test << std::endl;
    crypto.encrypt(test);
    std::cout << test << std::endl;
    */

    //Manager manager;
    //manager.setFilepath("data.crypt");
    //manager.readData();
    //manager.writeData(); 
    //std::cout << fileio::read("data");
    //Logger logger("out.log", 3);
    //logger.log(5, "this is just a test of level 5");
    return 0;
}
