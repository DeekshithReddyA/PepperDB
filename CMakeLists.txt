cmake_minimum_required(VERSION 3.16)

project(pepperdb VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(pepperdb
    src/main.cpp
    src/repl.cpp
    src/parser.cpp
    src/database.cpp
    src/executer.cpp

    common/utility.cpp
)

target_include_directories(pepperdb PRIVATE common)
