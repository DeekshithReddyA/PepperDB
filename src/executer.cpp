#include "executer.hpp"
#include "database.hpp"

void handle_SET(const std::string& key, const std::vector<std::string>& tokens ,Database& db){
    std::string value = "";
    
    for(int i = 2; i < tokens.size(); i++){
        value += tokens[i];
        if(i != tokens.size() - 1) value += " ";
    }
    
    db.set(key, value);
}
std::string handle_KEYS(Database& db){
    std::vector<std::string> keys = db.keys();
    std::string str = "";
    for(int i = 0; i < keys.size(); i++){
        if(i == keys.size() - 1) str += keys[i];
        else{
            str += keys[i];
            str += "\n";
        } 
    }

    return str;

}


std::string executeCommand(std::vector<std::string>& tokens){

    Database& db = Database::GetInstance();
    
    std::string command = tokens[0];
    std::transform(command.begin(), command.end(), command.begin() , ::toupper);
    
    
    
    if(command == "SET"){
        if(tokens.size() < 2){
            return "(error) Wrong number of arguments for 'SET'";
        }
        std::string key = tokens[1];
        
        handle_SET(key, tokens, db);
        return "OK";
        
    } else if(command == "GET"){
        if(tokens.size() < 2){
            return "(error) Wrong number of arguments for 'GET'";
        }

        std::string key = tokens[1];
        
        std::optional<std::string> res = db.get(key);
        
        if(res) 
        return res.value();
        
        return "(nil)";
        
    } else if(command == "DEL"){
        std::string key = tokens[1];
        
        if(db.deleteKey(key))
        return "(integer) 1";
        
        return "(integer) 0";
        
    } else if(command == "EXISTS"){
        std::string key = tokens[1];
    
        bool isExists = db.isExists(key);
        if(isExists) return "(integer) 1";
        
        return "(integer) 0";
    
    } else if(command == "COUNT"){
        
        int n = db.count();

        return "(integer) " + std::to_string(n);
    
    } else if(command == "KEYS"){

        return handle_KEYS(db);
        
    } else if(command == "CLEAR"){
        db.clear();

        return "OK";
    }


    return "(error) Unkown command: " + tokens[0];
}