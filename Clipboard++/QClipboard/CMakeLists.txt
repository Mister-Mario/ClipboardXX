add_library(QClipboard STATIC
    ClipboardInterface.h
    ClipboardAdapter.h
    ClipboardAdapter.cpp
    ClipboardListener.h
    ClipboardListener.cpp
    MemoryCells/MemoryCell.h
    MemoryCells/MemoryCell.cpp
    MemoryCells/MemoryCellManager.h
    MemoryCells/MemoryCellManager.cpp
    KeyShortCuts/KeyShortCut.h
    KeyShortCuts/KeyShortCut.cpp
    KeyShortCuts/KeyShortCutManager.h
    KeyShortCuts/KeyShortCutManager.cpp
    HotKeyListener/HotKeyListener.h
    HotKeyListener/HotKeyListener.cpp

)

# Set include directories
target_include_directories(QClipboard 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}  # So other targets can include files using "QClipboard/ClipboardInterface.h"
    PRIVATE
        ${CMAKE_SOURCE_DIR}  # To allow includes relative to project root
)

# Link Qt libraries
target_link_libraries(QClipboard 
    PUBLIC 
        Qt6::Gui
    PRIVATE
        ProjectUtils
        RmlUi::RmlUi
)