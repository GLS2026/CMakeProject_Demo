cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(NumericalProject main.cpp)
target_link_libraries(NumericalProject PRIVATE MathLib)

if(WIN32)
    add_custom_command(TARGET NumericalProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:MathLib>
            $<TARGET_FILE_DIR:NumericalProject>
        COMMENT "Copying MathLib DLL to NumericalProject directory"
    )
endif()

target_include_directories(NumericalProject PRIVATE MathLib)

install(TARGETS NumericalProject 
    RUNTIME DESTINATION bin
)

install(TARGETS MathLib
    EXPORT MathLibTargets
    DESTINATION bin
)

install(FILES ../math/inc/ODEFunction.hpp ../math/inc/utility.hpp
    DESTINATION inc
)

set_target_properties(NumericalProject PROPERTIES
    BUILD_RPATH "${CMAKE_BINARY_DIR}/math"
    INSTALL_RPATH "$ORIGIN"
)