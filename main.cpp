#include "database/databaseSystemManagment.h"

int main(){
    
    std::string filepath = "data.crypt";
    DatabaseSystemManagment dsm(filepath);
    dsm.readFromFile();
    //dsm.printData();
    
    /*
    std::string test = "1234";
    Crypto crypto("abc");
    std::cout << test << std::endl;
    crypto.encrypt(test);
    std::cout << test << std::endl;
    crypto.decrypt(test);
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
    //logger.debug("this is just some message");
    
    return 0;
}
