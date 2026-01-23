#pragma once

#include<vector>
#include<unordered_map>
#include<string>
#include<optional>
#include<iostream>

class Database{
private:
    std::unordered_map<std::string, std::string> store;
    Database() {}
    
public:
    static Database& GetInstance();
    void set(std::string key, std::string value);
    std::optional<std::string> get(std::string key);
    void print();
    bool deleteKey(std::string key);
};