#ifndef CRYPT_H_WAPUMCKS
#define CRYPT_H_WAPUMCKS

#include <string>
#include <vector>

class Crypto{

public:
    Crypto(std::string key);
    Crypto(size_t keyLength = 4096);

    void setKey(std::string key)	    {mKey = key;}
    void setKeyLenght(std::string lenght)   {mKeyLength = lenght}

    std::string getKey() const		    {return mKey;}
    
    void generateKey();  
    void encrypt(std::string &rData);

protected:
    std::vector<bool> toByte(char character);
    char	      toChar(std::vector<bool> byte);
    
    // The generated key will contain only lower-case alphabetical characters
    std::string mKey;
    size_t	mKeyLength;
};

#endif /* end of include guard: CRYPT_H_WAPUMCKS */
