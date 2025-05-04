find_package(Qt6 REQUIRED COMPONENTS Gui)

add_library(QClipboard STATIC
    ClipboardInterface.h
    ClipboardAdapter.h
    ClipboardAdapter.cpp
    MemoryCells/MemoryCell.h
    MemoryCells/MemoryCell.cpp
    MemoryCells/MemoryCellManager.h
    MemoryCells/MemoryCellManager.cpp
    Utils/StringUtils.h
    Utils/StringUtils.cpp
)

# Set include directories
target_include_directories(QClipboard 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}  # So other targets can include files using "QClipboard/ClipboardInterface.h"
)

# Link Qt libraries
target_link_libraries(QClipboard PUBLIC Qt6::Gui)