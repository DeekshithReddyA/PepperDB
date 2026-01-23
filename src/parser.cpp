#include "parser.hpp"


std::vector<std::string> parser(std::string line){
    std::vector<std::string> tokens;
    std::string token;
    
    std::istringstream iss(line);

    while(iss >> token){
        tokens.push_back(token);
    }

    return tokens;
}