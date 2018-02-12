#ifndef CRYPT_H_WAPUMCKS
#define CRYPT_H_WAPUMCKS

#include <string>

class Crypto{

public:
    Crypto();
    
    void setKey(std::string key)    {mKey = key;}
    
    std::string getKey()	    {return mKey;}
    
    void generateKey();
    
    void encrypt(std::string &rData);
    void decrypt(std::string &rData);

private:
    std::string mKey;
};

#endif /* end of include guard: CRYPT_H_WAPUMCKS */
