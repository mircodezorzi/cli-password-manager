#include <iostream>
#include <stdlib.h>
#include <bits/stdc++.h>

#include "crypt.h"

std::string Crypt::encrypt(std::string data){
    std::string result = "";
    char dataArray[data.length()];
    strcpy(dataArray, data.c_str());
    for(auto i : dataArray)
	result += i + 1;	
    return result;
}

std::string Crypt::decrypt(std::string data){
    std::string result = "";
    char dataArray[data.length()];
    strcpy(dataArray, data.c_str());
    for(auto i : dataArray)
	result += i - 1;
    return result;
}
