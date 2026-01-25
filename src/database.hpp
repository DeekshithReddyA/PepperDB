#pragma once

#include<vector>
#include<unordered_map>
#include<string>
#include<optional>
#include<iostream>
#include<ctime>

struct ValueWithExpiry{
    std::string value;
    std::optional<time_t> expires_at;  
};

class Database{
private:
    std::unordered_map<std::string, ValueWithExpiry> store;
    double nSamples = 0.10; // 10% of keys will be sampled in each expiry cycle
    Database() {}
    
public:
    static Database& GetInstance();
    void set(const std::string& key, const std::string& value, const std::optional<time_t> expiry);
    std::optional<ValueWithExpiry> get(const std::string& key);
    void print();
    bool deleteKey(const std::string& key);
    bool isExists(const std::string& key);
    int count();
    std::vector<std::string> keys();
    void clear();
    void expiry_cycle();
};