find_package(nlohmann_json REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui)

add_library(ProjectUtils STATIC
    StringUtils.h
    StringUtils.cpp
    TranslationManager.h
    TranslationManager.cpp
    LinkManager.cpp
)

target_include_directories(ProjectUtils 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries( ProjectUtils
    PRIVATE
        Qt6::Gui
        Qt::Core
        RmlUi::RmlUi
        nlohmann_json::nlohmann_json
)