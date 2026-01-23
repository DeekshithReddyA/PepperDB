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
    void set(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key);
    void print();
    bool deleteKey(const std::string& key);
    bool isExists(const std::string& key);
    int count();
    std::vector<std::string> keys();
    void clear();
};