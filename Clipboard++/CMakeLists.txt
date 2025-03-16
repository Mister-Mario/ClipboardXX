cmake_minimum_required(VERSION 3.10)

project(Clipboard++ LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest CONFIG REQUIRED)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Main executable
add_executable(${PROJECT_NAME} Clipboard++.cpp)

# Test executable
add_executable(${PROJECT_NAME}_test SimpleGTest.cpp)
target_link_libraries(${PROJECT_NAME}_test PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

# Enable testing
enable_testing()
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)