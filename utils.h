#ifndef UTILS_H_L5I0E1SZ
#define UTILS_H_L5I0E1SZ

#include <vector>
#include <string>

namespace utils{
inline void replace(std::string &str, std::string substr, std::string replacement);

std::string	  toHex(std::vector<bool> byte);
std::vector<bool> toByte(std::string hex);
}

#endif /* end of include guard: UTILS_H_L5I0E1SZ */
