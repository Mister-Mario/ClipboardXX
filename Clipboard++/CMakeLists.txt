cmake_minimum_required(VERSION 3.10)
project(Clipboard++ LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)  # Automatización de MOC para Qt6
set(CMAKE_AUTORCC ON)

set(CMAKE_BUILD_TYPE Debug)

find_package(SDL3 REQUIRED)
find_package(RmlUi REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(tinyfiledialogs CONFIG REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
find_package(magic_enum CONFIG REQUIRED)

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
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/RmlUI/ViewModels) 
add_subdirectory(RmlUI/ViewModels)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/RmlUI/EventHandlers) 
add_subdirectory(RmlUI/EventHandlers)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/RmlUI/Elements) 
add_subdirectory(RmlUI/Elements)


# Main executable
add_executable(${PROJECT_NAME} Clipboard++.cpp resources.qrc)

# Include RmlUi
target_link_libraries(${PROJECT_NAME} PRIVATE RmlUi::RmlUi rmlui_backend_SDL_GL3 rmlui_shell QClipboard EventHandlers Elements Qt6::Widgets)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        ${CMAKE_CURRENT_BINARY_DIR}/assets
    COMMENT "Copying assets directory to build directory"
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        ${CMAKE_CURRENT_BINARY_DIR}/Tests/assets
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

add_subdirectory(Tests)