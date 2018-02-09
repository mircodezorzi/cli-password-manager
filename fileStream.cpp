#include <fstream>

#include "fileStream.h"

std::string fileio::read(std::string path){
    std::ifstream in(path);
    std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return contents;
}

void fileio::write(std::string path, std::string data){
    std::ofstream outputFile(path);
    outputFile << data;
}
