#pragma once

#include<string>
#include<filesystem>
#include<fstream>
#include<iostream>

class AOF{
private:
    std::string filename;
    std::ofstream file;
    AOF(const std::string& filename);
public:
    static AOF& GetInstance();
    void create_dir_and_file_if_not_exists(const std::string& dir, const std::string& filename);
    void appendCommand(const std::string& command);
};