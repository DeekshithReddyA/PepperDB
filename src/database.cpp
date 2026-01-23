#include "database.hpp"

// Database::Database() {}

Database& Database::GetInstance(){
    static Database instance;
    return instance;
}

void Database::set(std::string key, std::string value){
    store[key] = value;
}

std::string Database::get(std::string key){
    if(store.find(key) == store.end()){
        return "(nil)";
    }

    return store[key];
}

