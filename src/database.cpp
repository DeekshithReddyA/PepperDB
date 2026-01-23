#include "database.hpp"

// Database::Database() {}

Database& Database::GetInstance(){
    static Database instance;
    return instance;
}

void Database::set(const std::string& key, const std::string& value){
    store[key] = value;
}

std::optional<std::string> Database::get(const std::string& key){
    if(!Database::isExists(key)) return std::nullopt;

    return store[key];
}

void Database::print(){
    for(auto it : store){
        std::cout << it.first << " : " << it.second << "\n";
    }
}

bool Database::deleteKey(const std::string& key){
    std::optional<std::string> res = Database::get(key);

    if(res){
        store.erase(key);
        return true;
    } else {
        return false;
    }
}

bool Database::isExists(const std::string& key){
    if(store.find(key) != store.end()) return true;

    return false;
}

int Database::count(){
    return store.size();
}

std::vector<std::string> Database::keys(){
    std::vector<std::string> ans;

    for(auto it : store){
        ans.push_back(it.first);
    }


    return ans;
}

void Database::clear(){
    store.clear();
}