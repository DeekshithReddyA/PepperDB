#include "repl.hpp"
#include "parser.hpp"
#include "executer.hpp"
#include "aof.hpp"

void runRepl(){
    std::cout << "PepperDB booted\n";
    std::cout << "Type 'exit' or 'quit' to leave. \n";
    
    std::string line;
    
    AOF& aofInstance = AOF::GetInstance();
    while(true){
        std::cout << "pepperdb> " << std::flush;
        
        if(!std::getline(std::cin , line)){
            std::cout << '\n';
            break;
        }
        Database::GetInstance().expiry_cycle();
        
        std::string temp = line;

        std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
        
        if(temp == "EXIT" || temp == "QUIT"){
            break;
        }

        if(line.empty()) continue;
        
        std::vector<std::string> tokens = parser(line);
        if(tokens.size() == 0) continue; 

        
        std::cout << executeCommand(tokens) << "\n";

        aofInstance.appendCommand(line);
        
    }

    std::cout << "PepperDB shutdown\n";
}