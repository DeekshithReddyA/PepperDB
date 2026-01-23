#pragma once

#include<vector>
#include<unordered_map>
#include<string>

class Database{
private:
    std::unordered_map<std::string, std::string> store;
    Database() {}
    
public:
    static Database& GetInstance();
    void set(std::string key, std::string value);
    std::string get(std::string key);
};