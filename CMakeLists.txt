cmake_minimum_required(VERSION 3.30)
project(dsa)

set(CMAKE_CXX_STANDARD 14)

include_directories(ArrayCPP/ArrayCPP)

add_executable(dsa
    Array/Array/main.c
    ArrayClass/ArrayClass/main.cpp
    ArrayCPP/ArrayCPP/array.cpp
    ArrayCPP/ArrayCPP/array.h
    ArrayCPP/ArrayCPP/main.cpp
    HelloWorld/DSA/main.c
    InitialPlayground/arrays.cpp
    InitialPlayground/cppClassesPractice.cpp
    InitialPlayground/funcs.cpp
    InitialPlayground/templateClass.cpp
    Recursion/Recursion/main.c
    StaticGlobal/StaticGlobal/main.c
    TailHead/TailHead/main.c
    TreeRecursion/TreeRecursion/main.c)
