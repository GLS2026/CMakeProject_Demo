cmake_minimum_required(VERSION 3.10)
project(SimpleApp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(../inc)

add_executable(TestApp src/main.cpp ../src/mysqrt.cpp)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")

install(TARGETS TestApp
    RUNTIME DESTINATION bin
)