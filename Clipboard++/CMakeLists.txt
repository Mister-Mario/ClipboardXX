cmake_minimum_required(VERSION 3.10)

project(Clipboard++ LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest CONFIG REQUIRED)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

find_package(RmlUi REQUIRED)
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Main executable
add_executable(${PROJECT_NAME} Clipboard++.cpp)
# Include RmlUi
target_link_libraries(${PROJECT_NAME} PRIVATE RmlUi::RmlUi)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Test executable
add_executable(${PROJECT_NAME}_test SimpleGTest.cpp)
target_link_libraries(${PROJECT_NAME}_test PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

# Enable testing
enable_testing()
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)