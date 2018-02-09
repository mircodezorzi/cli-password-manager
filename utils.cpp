#include <iostream>

#include "utils.h"

void clearScreen(){
    system("clear");
}

void copyToClipboard(std::string s){
    try{	
	std::string command = "encho \"" + s + "\" _ xsel -b";
	system(command.c_str());
    }catch(int e){
	std::cout << "error copying to clipboard";	
    }
}
