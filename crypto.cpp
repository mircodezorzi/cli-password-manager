#include "crypto.h"

#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>
#include <stdlib.h>

Crypto::Crypto(){
    generateKey();
}

void Crypto::generateKey(){
    srand(time(NULL));
    mKey = std::to_string(rand());
}

void Crypto::encrypt(std::string &rData){
    std::string result = "";
    char dataArray[rData.length()];
    strcpy(dataArray, rData.c_str());
    for(char i : dataArray)
	result += i + 1;	
    rData = result;
}

void Crypto::decrypt(std::string &rData){
    std::string result = "";
    char dataArray[rData.length()];
    strcpy(dataArray, rData.c_str());
    for(char i : dataArray)
	result += i - 1;
    rData = result;
}
