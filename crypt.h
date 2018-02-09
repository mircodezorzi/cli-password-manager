#ifndef CRYPT_H_WAPUMCKS
#define CRYPT_H_WAPUMCKS

#include <iostream>

class Crypt{

    public:
    std::string encrypt(std::string data);
    std::string decrypt(std::string data);

};

#endif /* end of include guard: CRYPT_H_WAPUMCKS */
