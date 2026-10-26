cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(../inc)
add_library(MySqrtLib SHARED 
    src/mysqrt.cpp
)

target_include_directories(MySqrtLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)