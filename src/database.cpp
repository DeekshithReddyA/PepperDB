#include "database.hpp"

// Database::Database() {}

Database& Database::GetInstance(){
    static Database instance;
    return instance;
}

void Database::set(std::string key, std::string value){
    store[key] = value;
}

std::optional<std::string> Database::get(std::string key){
    if(store.find(key) == store.end()){
        return std::nullopt;
    }

    return store[key];
}

void Database::print(){
    for(auto it : store){
        std::cout << it.first << " : " << it.second << "\n";
    }
}

bool Database::deleteKey(std::string key){
    std::optional<std::string> res = Database::get(key);

    if(res){
        store.erase(key);
        return true;
    } else {
        return false;
    }
}

