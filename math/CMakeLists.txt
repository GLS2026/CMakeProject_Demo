cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(MathLib SHARED 
    src/function.cpp
    src/utility.cpp
)

target_include_directories(MathLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)