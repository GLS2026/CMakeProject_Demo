cmake_minimum_required(VERSION 3.10)
project(SimpleApp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/install")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

include_directories("${PROJECT_SOURCE_DIR}/inc")

add_library(mysqrt5 SHARED src/mysqrt.cpp)
add_executable(SimpleApp src/main.cpp)

target_link_libraries(SimpleApp PRIVATE mysqrt5)

install(TARGETS SimpleApp RUNTIME DESTINATION bin)
install(TARGETS mysqrt5 LIBRARY DESTINATION lib)
install(TARGETS mysqrt5 ARCHIVE DESTINATION lib)
install(FILES inc/mysqrt.hpp DESTINATION inc)