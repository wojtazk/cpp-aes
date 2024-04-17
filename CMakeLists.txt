cmake_minimum_required(VERSION 3.27)
project(cpp_aes)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_aes main.cpp
        encryption.cpp
        decryption.cpp
        lookup_tables.h
        tests.cpp
        functions.h
        lookup_tables.cpp
        key_functions.cpp)
