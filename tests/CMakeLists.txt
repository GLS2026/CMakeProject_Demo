cmake_minimum_required(VERSION 3.14)
project(MathTests)

# 引入 Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 啟用 CTest 支援
enable_testing()

# 建立你的測試執行檔
add_executable(test_mysqrt test_mysqrt.cpp)

target_link_libraries(test_mysqrt
    PRIVATE
        MySqrtLib
        GTest::gtest_main
)

if(WIN32)
    add_custom_command(TARGET test_mysqrt POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:MySqrtLib>
            $<TARGET_FILE_DIR:test_mysqrt>
        COMMENT "Copying MySqrtLib DLL to test_mysqrt directory"
    )
endif()

# 讓 CTest 能夠自動發現並執行這個測試
include(GoogleTest)
gtest_discover_tests(test_mysqrt)

set_target_properties(test_mysqrt PROPERTIES
    BUILD_RPATH "${CMAKE_BINARY_DIR}/math"
    INSTALL_RPATH "$ORIGIN"
)

# --- 讓 CTest 的測試執行檔也能透過 cmake --install 產生到 install/bin ---
install(TARGETS test_mysqrt
    RUNTIME DESTINATION bin
)