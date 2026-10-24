cmake_minimum_required(VERSION 3.10)
project(SimpleApp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TestApp src/main.cpp)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")

install(TARGETS TestApp
    RUNTIME DESTINATION bin
)