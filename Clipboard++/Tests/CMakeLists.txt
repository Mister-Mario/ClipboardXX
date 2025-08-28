if(WIN32)
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()
find_package(GTest CONFIG REQUIRED)
# Enable testing
enable_testing()

# Test executable
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "*.cpp")
add_executable(${PROJECT_NAME}_test ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME}_test PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main ProjectUtils QClipboard RmlUi::RmlUi)


include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)