cmake_minimum_required(VERSION 3.10)
project(Clipboard++ LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)  # Automatización de MOC para Qt6
set(CMAKE_BUILD_TYPE Debug)

find_package(SDL3 REQUIRED)
find_package(RmlUi REQUIRED)

add_subdirectory(Utils)
add_subdirectory(QClipboard)


set(RMLUI_BACKEND SDL_GL3)
include(RmlUI/Utilities.cmake)
include(RmlUI/DependenciesForBackends.cmake)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/RmlUI/Backends)
add_subdirectory(RmlUI/Backends)
include(RmlUI/DependenciesForShell.cmake)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/RmlUI/Shell)
add_subdirectory(RmlUI/Shell)

add_subdirectory(RmlUI/EventHandlers)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/RmlUI/Elements) 
add_subdirectory(RmlUI/Elements)



# Main executable
add_executable(${PROJECT_NAME} Clipboard++.cpp)

# Include RmlUi
target_link_libraries(${PROJECT_NAME} PRIVATE RmlUi::RmlUi rmlui_backend_SDL_GL3 rmlui_shell QClipboard EventHandlers Elements)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        ${CMAKE_CURRENT_BINARY_DIR}/assets
    COMMENT "Copying assets directory to build directory"
)
# Copia las DLLs de Qt6 al directorio del ejecutable en Windows - DESPUÉS de definir el target
if(WIN32)
    get_target_property(_qmake_executable Qt6::qmake IMPORTED_LOCATION)
    get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
   
    # Detectar arquitectura (32 o 64 bits)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(ARCH "x64")
    else()
        set(ARCH "x86")
    endif()

    # Usa windeployqt en lugar de copiar manualmente (recomendado)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")
   
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND "${WINDEPLOYQT_EXECUTABLE}"
            --verbose 0
            --no-compiler-runtime
            "$<TARGET_FILE:${PROJECT_NAME}>"
        COMMENT "Deploying Qt6 dependencies using windeployqt"
    )
    
    # Copia el plugin de plataforma Windows desde la ubicación correcta
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/platforms
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_BINARY_DIR}/vcpkg_installed/${ARCH}-mingw-dynamic/Qt6/plugins/platforms/qwindows.dll
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/platforms
    )
endif()



if(WIN32)
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()
find_package(GTest CONFIG REQUIRED)
# Enable testing
enable_testing()

# Test executable
add_executable(${PROJECT_NAME}_test SimpleGTest.cpp)
target_link_libraries(${PROJECT_NAME}_test PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)


include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)