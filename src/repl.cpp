#include "repl.hpp"
#include "parser.hpp"

void runRepl(){
    std::cout << "PepperDB booted\n";
    std::cout << "Type 'exit' or 'quit' to leave. \n";

    std::string line;

    while(true){
        std::cout << "pepperdb>" << std::flush;

        if(!std::getline(std::cin , line)){
            std::cout << '\n';
            break;
        }

        if(line == "exit" || line == "quit"){
            break;
        }

        if(line.empty()) continue;
        
        std::vector<std::string> tokens = parser(line);

        std::cout << "tokens parsed (checked for whitespaces)" << '\n';
        
    }

    std::cout << "PepperDB shutdown\n";
}