add_library(ProjectUtils STATIC
    StringUtils.h
    StringUtils.cpp
    TranslationManager.h
    TranslationManager.cpp
    LinkManager.h
    LinkManager.cpp
    FileManager.h
    FileManager.cpp
    IFileManager.h
)

target_include_directories(ProjectUtils 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries( ProjectUtils
    PRIVATE
        Qt6::Gui
        Qt6::Core
        RmlUi::RmlUi
        nlohmann_json::nlohmann_json
        tinyfiledialogs::tinyfiledialogs
        magic_enum::magic_enum
)
