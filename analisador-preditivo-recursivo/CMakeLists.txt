cmake_minimum_required(VERSION 3.12)
project(analisador_preditivo_recursivo)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(analisador_preditivo_recursivo
        CMakeLists.txt
        main.cpp)
