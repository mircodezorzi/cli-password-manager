#ifndef CRYPT_H_WAPUMCKS
#define CRYPT_H_WAPUMCKS

#include <string>
#include <vector>

class Crypto{

public:
    Crypto(std::string key);
    Crypto(size_t keyLength = 4096);

    void setKey(std::string key)	    {mKey = key;}
    void clearKey()			    {mKey = "";}

    std::string getKey()		    {return mKey;}
    
    void generateKey();
     
    void encrypt(std::string &rData);
    void decrypt(std::string &rData);

private:
    std::vector<bool> toByte(char character);
    char	      toChar(std::vector<bool> byte);
    
    std::string mKey;
    size_t	mKeyLength;
};

#endif /* end of include guard: CRYPT_H_WAPUMCKS */
