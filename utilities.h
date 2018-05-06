
#ifndef UTILITIES_H_NTDF321X
#define UTILITIES_H_NTDF321X

#include<string>

namespace utilities{
    
    bool	containsCharacters(std::string str, char c, size_t num);
    
    char        charIfCondition(char c, bool condition);
    
    size_t      shift(size_t num, size_t shifted, size_t reset);
    size_t	find(std::string str, const char *c, size_t ordinal);
    
    void	removeSpacesUntill(std::string &str, char c);
    void        replace(std::string& str, std::string substr, std::string replacement);
 
    std::string substring(std::string str, const char *separator); 
    std::string substring(std::string str, std::string firstSeparator, std::string secondSeparator);
    std::string multiply(char c, size_t num);
    std::string multiply(std::string str, size_t num);
    std::string insertLineNumber(std::string str, size_t num);

};


#endif /* end of include guard: UTILITIES_H_NTDF321X */

