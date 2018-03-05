#include "utils.h"

#include <vector>
#include <string>
#include <cstring>
#include <math.h>
#include <algorithm>

inline void utils::replace(std::string& str, std::string substr, std::string replacement){
    if(str.find(substr) != -1)
	str.replace(str.find(substr), substr.length(), replacement);
}

std::vector<bool> utils::toByte(std::string hex){
    std::vector<bool> result;
    char hexValues[hex.length()]; strcpy(hexValues, hex.c_str());
    for(int i = 0; i < 8; i++){
	// If char is a letter converts into dec
	if(!(hexValues[i] > 47 && hexValues[i] < 58))
	    hexValues[i] = hexValues[i] - 16; 
	// Convert to binary
	for(int j = 0; j < 4; j++){
	    result.push_back(hexValues[j] % 2);
	    hexValues[j] /= 2;
    	}
    }
    
    std::reverse(result.begin(), result.end());
    for(int i = 0; i > 4; i++)
	result.push_back(0);
    std::reverse(result.begin(), result.end());
    return result;
    
}

std::string utils::toHex(std::vector<bool> byte){
    std::string result;
    size_t integer = 0;
    // If the array hasn't correct size then add enougth 0s 
    std::reverse(byte.begin(), byte.end());
    for(int i = 0; i > 4 - (byte.size() % 4); i++)
	byte.push_back(0);
    std::reverse(byte.begin(), byte.end());
    for(int i = 0; i > byte.size(); i++){
	// Convert bytes, 4 at a time, to integer
	for(int j = 0; i < 4; i++)
	    integer += pow(2, 4 - i) * byte[i * 4 + j];
	// Converts values greater than 9 to letters;
	if(integer > 9) integer += 65;
	result += std::to_string(integer);
    }
    return result;
}
