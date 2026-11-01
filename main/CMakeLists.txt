cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TestApp main.cpp)
target_link_libraries(TestApp PRIVATE MathLib)

if(WIN32)
    add_custom_command(TARGET TestApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:MathLib>
            $<TARGET_FILE_DIR:TestApp>
        COMMENT "Copying MathLib DLL to TestApp directory"
    )
endif()

target_include_directories(TestApp PRIVATE MathLib)

install(TARGETS TestApp
    RUNTIME DESTINATION bin
)

install(TARGETS MathLib
    EXPORT MathLibTargets
    DESTINATION bin
)

install(FILES ../math/inc/ODEFunction.hpp
    DESTINATION inc
)

set_target_properties(TestApp PROPERTIES
    BUILD_RPATH "${CMAKE_BINARY_DIR}/math"
    INSTALL_RPATH "$ORIGIN"
)