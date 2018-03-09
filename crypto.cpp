#include "crypto.h"
#include "utils.h"

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

void Cryto::uniform(std::vector<bool> &vec, size_t count){
    std::reverse(vec.begin(), vec.end());
    for(int i = 0; i < vec.size() % count; i++)
    	vec.push_back(0);
    std::reverse(vec.begin(), vec.end()); 
}

std::string Crypto::toHex(std::vector<bool> byte){
    std::string result = "";  
    uniform(byte, 4);
    for(int i = 0; i < byte.size(); i += 4){
	size_t value = 0;		
	for(int j = 0; j < 4; j++)
	    value += pow(2, 3 - j) * byte[j + i];
	if(!value > 9)  
	    result += std::to_string(value);
	else		     
	    result += (char) value + 56;
    }
    return result;
}

std::vector<bool> utils::toByte(std::string hex){
    std::vector<bool> result;
    char hexValues[hex.length()]; strcpy(hexValues, hex.c_str());
    for(int i = 0; i < 8; i++){
	if(!(hexValues[i] > 47 && hexValues[i] < 58))
	    hexValues[i] = hexValues[i] - 16; 
	for(int j = 0; j < 4; j++){
	    result.push_back(hexValues[j] % 2);
	    hexValues[j] /= 2;
    	}
    } 
    return result;
    
}

void Crypto::encrypt(std::string &rData){
    std::vector<bool> binaryChar, binaryKey, binaryResult;

    std::string encryptedData = "";
    
    char data[rData.length()],\
	 key [mKey.length()];
   
    strcpy(dataArray, rData.c_str());
    strcpy(keyArray, mKey.c_str());
    
    for(int i = 0; i < sizeof(data_array); i++){
	binary_character = utils::toByte(data_array[i]);
	binary_key       = utils::toByte(key_array[i % sizeof(key_array)]);

	for(int j = 0; j < 8; j++)
	    binary_result.push_back(binary_character[j] ^ binary_key[j]); 

	encrypted_data += utils::toHex(binary_result);

	binary_key.clear();
	binary_character.clear();
	binary_result.clear();
    }
    rData = encrypted_data;
}


