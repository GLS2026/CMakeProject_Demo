cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TestApp main.cpp)
target_link_libraries(TestApp PRIVATE MySqrtLib)

if(WIN32)
    add_custom_command(TARGET TestApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:MySqrtLib>
            $<TARGET_FILE_DIR:TestApp>
        COMMENT "Copying MySqrtLib DLL to TestApp directory"
    )
endif()

target_include_directories(TestApp PRIVATE MySqrtLib)

install(TARGETS TestApp
    RUNTIME DESTINATION bin
)

install(TARGETS MySqrtLib
    EXPORT MySqrtLibTargets
    DESTINATION bin
)

install(FILES ../math/inc/mysqrt.hpp
    DESTINATION inc
)

set_target_properties(TestApp PROPERTIES
    BUILD_RPATH "${CMAKE_BINARY_DIR}/math"
    INSTALL_RPATH "$ORIGIN"
)