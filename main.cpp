#include "databaseSystemManagment.h"
#include "manager.h"

int main(){
    //std::string filepath = "data.crypt";
    //DatabaseSystemManagment dsm(filepath);
    //dsm.import();

    /*
    Display display;
    char input;
    display.printFrame(0);
    display.printBottomFrame();
    display.printMiddle(0, "test");
    display.setCursor(); 
    do{
	input = display.getInput();
    }while(input != 'q');
    */

    /*
    std::string test = "1234";
    
    Crypto crypto("abc");
    std::cout << test << std::endl;
    
    crypto.encrypt(test);
    std::cout << test << std::endl;
    
    crypto.decrypt(test);
    std::cout << test << std::endl;
    */

    Manager manager;
    //manager.setFilepath("data.crypt");
    //manager.readData();
    //manager.writeData(); 
    //std::cout << fileio::read("data");
    manager.start();
    //Logger logger("out.log", 3);
    //logger.log(5, "this is just a test of level 5");
    //logger.debug("this is just some message");
    
    return 0;
}
