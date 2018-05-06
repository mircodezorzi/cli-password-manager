#ifndef CRYPT_H_WAPUMCKS
#define CRYPT_H_WAPUMCKS

#include<string>
#include<vector>
#include<fstream>

#include<boost/variant.hpp>

class Crypto{

public:
    Crypto(std::string key);
    Crypto(size_t keyLength = 4096);

    void setKey	     (std::string k)	    {mKey = k;}
    void setKeyLenght(size_t l)	            {mKeyLength = l;}

    std::string getKey() const		    {return mKey;}
    
    void generateKey();  

    void encrypt(std::string &rData);
    void decrypt(std::string &rData);

protected:
    std::fstream fileStream;
    
    // Makes an array of size multiple of count. eg: count = 5, array size = 7; new array size = 10
    template <typename T>
    void uniform(std::vector<T> &vec, T element, size_t count);
    
    std::vector<bool> toByte(std::string hex);
    
    char    toChar(std::vector<bool> byte); 
    std::string    toChar(size_t value);
    std::vector<bool> toByte(char character);

    std::string toHex(std::vector<bool> byte);
	
    // The generated key will contain only lower-case alphabetical characters
    std::string mKey;
    size_t	mKeyLength;
};

#endif /* end of include guard: CRYPT_H_WAPUMCKS */
