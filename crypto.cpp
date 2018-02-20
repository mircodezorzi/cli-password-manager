#include "crypto.h"

#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <vector>
#include <bitset>
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
    srand(time(NULL));
    for (int i = 0; i < mKeyLength; i++)
	mKey += (rand() % 26) + 97; 
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

char Crypto::toChar(std::vector<bool> byte){
    int result = 0;
    for(int i = 0; i < 8; i++)
	result += byte[i] * pow(2, 8 - i);
    return result;
}

void Crypto::encrypt(std::string &rData){
    std::string encrypted_data = "";
    std::vector<bool> binary_character, binary_key, binary_result;
    
    char data_array[rData.length()];
    strcpy(data_array, rData.c_str());

    char key_array[mKey.length()];
    strcpy(key_array, mKey.c_str());
    
    for(int i = 0; i < sizeof(data_array); i++){
	
	binary_character = toByte(data_array[i]);
	binary_key       = toByte(key_array[i % sizeof(key_array)]);

	for(int j = 0; j < 8; j++)
	    binary_result.push_back(binary_character[j] ^ binary_key[j]); 
	 
	encrypted_data += toChar(binary_result);
    
	//
	std::cout << std::endl << "data:   ";
	for(auto n:binary_character)
	    std::cout << n;
	std::cout << std::endl << "key:  " << key_array[i % sizeof(key_array)] << " ";
	for(auto n:binary_key)
	    std::cout << n;
	std::cout << std::endl << "result: ";
	for(auto n:binary_result)
	    std::cout << n;
	std::cout << std::endl << "char: " << data_array[i] << "  ->  " << toChar(binary_result) << std::endl;
	std::cout << (int)data_array[i] << " " << (int)toChar(binary_result) << std::endl;
	//
	
	binary_key.clear();
	binary_character.clear();
	binary_result.clear();
    }
    rData = encrypted_data;
}

void Crypto::decrypt(std::string &rData){
    std::string result = "";
    char data_array[rData.length()];
    strcpy(data_array, rData.c_str());
    
    char key_array[rData.length()];
    strcpy(key_array, rData.c_str());

    rData = result;
}
