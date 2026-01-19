#include "parser.hpp"

std::string parser(std::string line){
    std::vector<std::string> tokens;
    std::string token;
    
    std::istringstream iss(line);

    while(iss >> token){
        tokens.push_back(token);
    }


    for(auto i : tokens){
        std::cout << i <<  " ";
    }

    std::cout << std::endl;

    return "";
}