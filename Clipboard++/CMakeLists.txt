cmake_minimum_required(VERSION 3.10)

project(Clipboard++ LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest CONFIG REQUIRED)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

find_package(SDL3 REQUIRED)
find_package(RmlUi REQUIRED)
set(RMLUI_BACKEND SDL_GL3)
include(RmlUI/Utilities.cmake)
include(RmlUI/DependenciesForBackends.cmake)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/RmlUI/Backends)
add_subdirectory(RmlUI/Backends)
include(RmlUI/DependenciesForShell.cmake)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/RmlUI/Shell)
add_subdirectory(RmlUI/Shell)


# Main executable
add_executable(${PROJECT_NAME} Clipboard++.cpp)
# Include RmlUi
target_link_libraries(${PROJECT_NAME} PRIVATE RmlUi::RmlUi rmlui_backend_SDL_GL3 rmlui_shell)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Test executable
add_executable(${PROJECT_NAME}_test SimpleGTest.cpp)
target_link_libraries(${PROJECT_NAME}_test PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

# Enable testing
enable_testing()
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)