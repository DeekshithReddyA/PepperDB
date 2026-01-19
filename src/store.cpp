#include "store.hpp"

class GlobalStore{
    private:
        std::set<std::string> commands;
    public:
        GlobalStore(){
            this->commands = {"PING", "ECHO", "HELP", "SET"};
        }

        bool isCommandValid(const std::string& command){
            return this->commands.find(command) != commands.end();
        }
        
};