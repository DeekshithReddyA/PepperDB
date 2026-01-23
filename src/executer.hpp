#pragma once

#include<vector>
#include<string>
#include<set>
#include<algorithm>
#include "database.hpp"

void handle_SET(const std::string& key, const std::vector<std::string>& tokens, Database& db);
std::string handle_KEYS(Database& db);
std::string executeCommand(std::vector<std::string>& tokens);