#include "programManager.h"

int main(){

    ProgramManager pm("data.crypt");
    pm.start();
    
    /*
    std::string test = "1234";
    
    Crypto crypto("abc");
    std::cout << test << std::endl;
    
    crypto.encrypt(test);
    std::cout << test << std::endl;
    
    crypto.decrypt(test);
    std::cout << test << std::endl;
    */

    //Logger logger("out.log", 3);
    //logger.log(5, "this is just a test of level 5");
    //logger.debug("this is just some message");
    
    return 0;
}
