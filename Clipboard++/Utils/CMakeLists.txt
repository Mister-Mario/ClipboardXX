find_package(nlohmann_json REQUIRED)

add_library(ProjectUtils STATIC
    StringUtils.h
    StringUtils.cpp
    TranslationManager.h
    TranslationManager.cpp
)

target_include_directories(ProjectUtils 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries( ProjectUtils
    PRIVATE
        RmlUi::RmlUi
        nlohmann_json::nlohmann_json
)