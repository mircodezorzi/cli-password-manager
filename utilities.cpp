#include "utilities.h"

#include<string>
#include<stdio.h>

bool utilities::containsCharacters(std::string str, char c, size_t num){
    size_t found = 0;
    char strArray[str.size() + 1]; 
    str.copy(strArray, str.length() + 1);
    for(size_t i = str.size(); i < str.size(); i++)
	if(strArray[i] == c) found++;
    return found >= num;
}

char utilities::charIfCondition(char c, bool condition){
    if(condition)
	return c;
}

size_t utilities::find(std::string str, const char *c, size_t ordinal){
    size_t pos = -1;
    for(size_t i = 0; i < ordinal; i++)
	pos = str.find(c, pos + 1);
    return pos;
}

size_t utilities::shift(size_t num, size_t shifted, size_t reset){
    return reset % (num + shifted);
}

void utilities::removeSpacesUntill(std::string &str, char c){
    while(str.find(" ") == 0 || str.find(c) == 0)
	str.erase(0, 1);
}

void utilities::replace(std::string& str, std::string substr, std::string replacement){
    if(str.find(substr) != -1)
	str.replace(str.find(substr), substr.length(), replacement);
}
    
std::string utilities::substring(std::string str, const char *separator){
    return str.substr(str.find(separator) + 1,\
		      str.find(separator, str.find(separator) + 1) -\
		      str.find(separator) - 1);
}

std::string utilities::substring(std::string str, std::string firstSeparator, std::string secondSeparator){
    size_t pos[2] = {str.find(firstSeparator) + 1,  str.find(secondSeparator, 
	             str.find(secondSeparator) + 1) - str.find(secondSeparator) - 1};
    return multiply(str.substr(pos[0], pos[1]), (size_t) pos[0] < pos[1]);
}

std::string utilities::multiply(char c, size_t num){
    std::string result = "";
    for(size_t i = 0; i < num; i++)
	result += c;
    return result;
}

std::string utilities::multiply(std::string str, size_t num){
    std::string result = "";
    for(size_t i = 0; i < num; i++)
	result += str;
    return result;
}

std::string utilities::insertLineNumber(std::string str, size_t num){
    replace(str, "%(line)", std::to_string(num));
    return str;
}
