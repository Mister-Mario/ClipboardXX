add_library(ClipboardLogic STATIC
    Clipboard/ClipboardInterface.h
    Clipboard/ClipboardAdapter.h
    Clipboard/ClipboardAdapter.cpp
    Clipboard/ClipboardListener.h
    Clipboard/ClipboardListener.cpp
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
target_include_directories(ClipboardLogic 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}  # So other targets can include files using "ClipboardLogic/Clipboard/ClipboardInterface.h"
    PRIVATE
        ${CMAKE_SOURCE_DIR}  # To allow includes relative to project root
)

# Link Qt libraries
target_link_libraries(ClipboardLogic 
    PUBLIC 
        Qt6::Gui
    PRIVATE
        ProjectUtils
        RmlUi::RmlUi
)