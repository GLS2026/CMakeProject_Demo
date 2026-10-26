cmake_minimum_required(VERSION 3.10)
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install"
    CACHE PATH "Install directory" FORCE
)
project(SimpleApp CXX)

add_subdirectory(math) 

add_subdirectory(main)