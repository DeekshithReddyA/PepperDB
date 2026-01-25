#include "database.hpp"

// Database::Database() {}

Database& Database::GetInstance(){
    static Database instance;
    return instance;
}

void Database::set(const std::string& key, const std::string& value,const std::optional<time_t> expiry){
    ValueWithExpiry val {value, expiry};
    store[key] = val;
}

std::optional<ValueWithExpiry> Database::get(const std::string& key){
    if(!Database::isExists(key)) return std::nullopt;

    return store[key];
}

void Database::print(){
    for(auto it : store){
        std::cout << it.first << " : " << it.second.value;
        if(it.second.expires_at){
            std::cout << it.second.expires_at.value();
        }
        std::cout << "\n";
    }
}

bool Database::deleteKey(const std::string& key){
    std::optional<ValueWithExpiry> res = Database::get(key);

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

void Database::expiry_cycle(){
    int sampleSize = std::max(1, static_cast<int>(nSamples * store.size()));
    std::vector<std::string> keysList = this->keys();

    auto it = store.begin();
    while(sampleSize-- && !store.empty()){
        if(it == store.end()){
            it = store.begin();
        }

        std::string key = it->first;
        std::optional<time_t> expiry = it->second.expires_at;

        if(expiry){
            time_t currentTime = std::time(nullptr);
            if(currentTime >= expiry.value()){
                store.erase(it++);
                continue;
            }
        }
        ++it;
    }
}