#include "crypto.h"

#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>

Crypto::Crypto(std::string key){
    mKey       = key;
    mKeyLength = key.length();
}

Crypto::Crypto(size_t keyLength){
    mKeyLength = keyLength;
    generateKey();
}

void Crypto::generateKey(){
    for (int i = 0; i < mKeyLength; i++)
	mKey += (rand() % 26) + 97;
}

char Crypto::toChar(std::vector<bool> byte){
    int result = 0;
    for(int i = 0; i < byte.size(); i++)
	result += byte[i] * pow(2, byte.size() - i);
    return result;
}

template <typename T>
void Crypto::uniform(std::vector<T> &vec, T element, size_t count){
    std::reverse(vec.begin(), vec.end());
    for(int i = 0; i < vec.size() % count; i++)
    	vec.push_back(element);
    std::reverse(vec.begin(), vec.end()); 
}

std::string Crypto::toHex(std::vector<bool> byte){
    std::string result = "";  
    uniform(byte, false, 4);
    for(int i = 0; i < byte.size(); i += 4){
	size_t value = 0;		
	for(int j = 0; j < 4; j++)
	    value += pow(2, 3 - j) * byte[j + i];
	if(!(value > 9))  
	    result += std::to_string(value);
	else		     
	    result += std::to_string((char) value + 56);
    }
    return result;
}

std::vector<bool> Crypto::toByte(char character){
    std::vector<bool> result;
    for(int i = 0; i < 8; i++){
	result.push_back(character % 2);
	character /= 2;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::vector<bool> Crypto::toByte(std::string hex){
    std::vector<bool> result;
    char hexValues[hex.length()]; strcpy(hexValues, hex.c_str());
    for(int i = 0; i < 2; i++){
	if(hexValues[i] > 47 && hexValues[i] < 58)
	    hexValues[i] = hexValues[i] - 48;
	else
	    hexValues[i] -= 65;

	for(int j = 0; j < 4; j++){
	    result.push_back(hexValues[j + 4 * i] % 2);
	    hexValues[j + 4 * i] /= 2;
    	}
    } 
    return result;
    
}

void Crypto::encrypt(std::string &rData){
    std::vector<bool> binaryChar, binaryKey, binaryResult;
    std::vector<char> data, key;
    
    std::copy(rData.begin(), rData.end(), std::back_inserter(data));
    std::copy(mKey.begin(),  mKey.end(),  std::back_inserter(key));

    std::string encryptedData = "";
   
    //for(int i = 0; i < sizeof(data); i++){
    for(int i = 0; i < 4; i++){
	binaryChar = toByte(data[i]);
	binaryKey  = toByte(key[i % sizeof(key)]);

	for(int j = 0; j < 8; j++)
	    binaryResult.push_back(binaryChar[j] ^ binaryKey[j]); 
	
	encryptedData += toHex(binaryResult);
	
	binaryKey.clear();
	binaryChar.clear();
	binaryResult.clear();
    }
    data.clear();
    key.clear();
    rData = encryptedData;
}

void Crypto::decrypt(std::string &rData){
    std::vector<bool> binaryChar, binaryKey, binaryResult;
    std::vector<char> data, key;
   
    std::string decryptedData = "";
 
    std::copy(rData.begin(), rData.end(), std::back_inserter(data));
    std::copy(mKey.begin(),  mKey.end(),  std::back_inserter(key));

    uniform(data, char(48), 2);
    
    //for(int i = 0; i < sizeof(data); i+=2){
    for(int i = 0; i < 8; i+=2){
	binaryChar = toByte(std::string(1, data[i]) + std::string(1, data[i + 1]));
	binaryKey  = toByte(std::string(1, key[(i % sizeof(key)) / 2]));
		
	for(int j = 0; j < 8; j++)
	    binaryResult.push_back(binaryChar[j] ^ binaryKey[j]);
	
	decryptedData += toChar(binaryResult);

	binaryKey.clear();
	binaryChar.clear();
	binaryResult.clear();

    }
    data.clear();
    key.clear();
    rData = decryptedData;
}
