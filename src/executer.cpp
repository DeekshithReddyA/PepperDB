#include "executer.hpp"
#include "database.hpp"
 
long checkTime(const std::optional<time_t> resTime, Database& db){
    long timeLeft;
    if(resTime){
        time_t currTime = std::time(nullptr);
        timeLeft = resTime.value() - currTime;
        if(timeLeft < 0){
            return -2;
        }
    } else {
        return -1;
    }

    return timeLeft;
}

std::string handle_SET(const std::vector<std::string>& tokens ,Database& db){
    if(tokens.size() <= 2){
        return "(error) Wrong number of arguments for 'SET'";
    }
    
    if(tokens.size() > 5){
        if(tokens[2][0] != '"')
            return "(error) ERR syntax error";
    }
    
    std::string key = tokens[1];
    std::string value = "";
    std::optional<time_t> expiry;
    int n = tokens.size();
    int i = 2;
    if(tokens[2][0] != '"'){
        value = tokens[2];
        i = 2;
    } else {
        for(i = 2; i < n; i++){
            value += tokens[i];
            if(tokens[i][tokens[i].size() - 1] == '"') break;
            if(i != n - 1) value += " ";
        }
    }
    if(n > i + 1){
        std::string ex = tokens[i + 1];
        std::transform(ex.begin(), ex.end(), ex.begin(), ::toupper);
        if((ex != "EX") || (n - (i + 1)) > 2){
            return "(error) ERR syntax error";
        }

        for(char c : tokens[n - 1]){
            if(c < '0' || c > '9'){
                return "(error) ERR invalid expire time in 'set' command";
            }
        }

        

        expiry = std::time(nullptr) + std::stol(tokens[i + 2]);
    }
    
    db.set(key, value, expiry);

    return "OK";
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
        return handle_SET(tokens, db);
        return "OK";
        
    } else if(command == "GET"){
        if(tokens.size() < 2){
            return "(error) Wrong number of arguments for 'GET'";
        }

        std::string key = tokens[1];
        
        std::optional<ValueWithExpiry> res = db.get(key);
        
        if(res){
            std::optional<time_t> resTime = res.value().expires_at;

            long time = checkTime(resTime, db);

            if(time == -2){
                db.deleteKey(key);

                return "(nil)";
            }

            return res.value().value;
        } 
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
    } else if(command == "TTL"){
        if(tokens.size() > 2 || tokens.size() < 2) return "(err) Invalid arguements";

        std::string key = tokens[1];

        std::optional<ValueWithExpiry> res = db.get(key);

        if(res){
            long time = checkTime(res.value().expires_at, db); 

            return "(integer) " + std::to_string(time);  
        }

        return "(integer) -2";
    }


    return "(error) Unkown command: " + tokens[0];
}