#ifndef CRYPT_H_WAPUMCKS
#define CRYPT_H_WAPUMCKS

#include <string>
#include <vector>
#include <fstream>

class Crypto{

public:
    Crypto(std::string key);
    Crypto(size_t keyLength = 4096);

    void setKey	     (std::string k)	    {mKey = k;}
    void setKeyLenght(size_t l)	            {mKeyLength = l;}

    std::string getKey() const		    {return mKey;}
    
    void generateKey();  
    void encrypt(std::string &rData);

protected:
    std::fstream fileStream;
 
    // The generated key will contain only lower-case alphabetical characters
    std::string mKey;
    size_t	mKeyLength;
};

#endif /* end of include guard: CRYPT_H_WAPUMCKS */
