#include "executer.hpp"
#include "database.hpp"


std::string executeCommand(std::vector<std::string>& tokens){
    std::string command = tokens[0];
    Database& db = Database::GetInstance();

    std::transform(command.begin(), command.end(), command.begin() , ::toupper);
    std::string key = tokens[1];



    if(command == "SET"){
        std::string value = "";

        for(int i = 2; i < tokens.size(); i++){
            value += tokens[i];
            if(i != tokens.size() - 1) value += " ";
        }

        db.set(key, value);

        return "OK";
    } else if(command == "GET"){
        std::optional<std::string> res = db.get(key);

        if(res){
            return res.value();
        } else{
            return "(nil)";
        }
    } else if (command == "DEL"){
        if(db.deleteKey(key)){
            return "1";
        } else{
            return "0";
        }
    } 
    return "";
}