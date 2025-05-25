add_library(ProjectUtils STATIC
    StringUtils.h
    StringUtils.cpp
)

target_include_directories(ProjectUtils 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)