#include "utils.h"

#include <vector>
#include <string>
#include <cstring>
#include <math.h>
#include <algorithm>

std::vector<bool> utils::toByte(char character){
    std::vector<bool> result;
    for(int i = 0; i < 8; i++){
	result.push_back(character % 2);
	character /= 2;
    }
    std::reverse(result.begin(), result.end());
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

char utils::toChar(std::vector<bool> byte){
    int result = 0;
    for(int i = 0; i < byte.size(); i++)
	result += byte[i] * pow(2, byte.size() - i);
    return result;
}

std::string utils::toHex(std::vector<bool> byte){
    std::string result = "";  
    utils::uniform(byte, 4);
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

void utils::uniform(std::vector<bool> &vec, size_t count){
    std::reverse(vec.begin(), vec.end());
    for(int i = 0; i < vec.size() % count; i++)
    	vec.push_back(0);
    std::reverse(vec.begin(), vec.end()); 
}
