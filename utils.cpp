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

char utils::toChar(std::vector<bool> byte){
    int result = 0;
    for(int i = 0; i < byte.size(); i++)
	result += byte[i] * pow(2, byte.size() - i);
    return result;
}

