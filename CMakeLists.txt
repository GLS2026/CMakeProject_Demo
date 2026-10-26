cmake_minimum_required(VERSION 3.10)
project(SimpleApp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(../inc)
add_library(MySqrtLib STATIC 
    src/mysqrt.cpp
)

add_executable(TestApp src/main.cpp)
target_link_libraries(TestApp PRIVATE MySqrtLib)

set_target_properties(TestApp PROPERTIES 
    BUILD_WITH_INSTALL_RPATH TRUE 
    INSTALL_RPATH "$ORIGIN" 
)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")

install(TARGETS TestApp
    RUNTIME DESTINATION bin
)

install(TARGETS MySqrtLib
    EXPORT MySqrtLibTargets
    DESTINATION bin
)

install(FILES inc/mysqrt.hpp
    DESTINATION inc
)