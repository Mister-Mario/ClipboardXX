add_library(ViewModels STATIC
    ShortCutsViewModel.h
    ShortCutsViewModel.cpp
    EditViewModel.h
    EditViewModel.cpp
)

# Set include directories
target_include_directories(ViewModels 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}  # For local includes
    PRIVATE
        ${CMAKE_SOURCE_DIR}  # To allow includes relative to project root
)

# Link dependencies
target_link_libraries(ViewModels 
    PUBLIC 
        RmlUi::RmlUi
    PRIVATE 
        ClipboardLogic
        ProjectUtils
)