//#include <ncurses.h>

//#include "utils.h"
//#include "crypt.h"
//#include "fileStream.h"

#include "utils.h"
#include "databaseSystemManagment.h"

//#include "logger.h"
#include "manager.h"
#include "crypto.h"

#include <math.h>
#include <iostream>
#include <vector>

int main(){

    //DatabaseSystemManagment dsm;
    //dsm.readData();
    //dsm.printData();
     
    std::string test = "1234";
    Crypto crypto("abc");
    std::cout << test << std::endl;
    crypto.encrypt(test);
    std::cout << test << std::endl;
    crypto.decrypt(test);
    std::cout << test << std::endl;
    /*
    crypto.encrypt(test);
    std::cout << test << std::endl;  
    */

    Manager manager;
    manager.setFilepath("data.crypt");
    manager.readData();
    //manager.writeData(); 
    //std::cout << fileio::read("data");
    //Logger logger("out.log", 3);
    //logger.log(5, "this is just a test of level 5");
    return 0;
}
