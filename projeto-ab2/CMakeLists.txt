cmake_minimum_required(VERSION 3.14)
project(projeto_ab2)

set(CMAKE_CXX_STANDARD 14)

add_executable(esc esc.cpp src/Parser.cpp src/Parser.h
        ../projeto-ab1/src/Tokenizer.h ../projeto-ab1/src/Tokenizer.cpp
        ../projeto-ab1/src/Category.hpp ../projeto-ab1/src/Category.cpp
        )