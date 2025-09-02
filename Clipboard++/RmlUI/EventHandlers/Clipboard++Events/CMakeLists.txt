add_library(Events STATIC
    Clipboard++Event.h
    WindowFocusEvent.h
    WindowFocusEvent.cpp

    Edit/EditEvent.h
    Edit/EditEvent.cpp
    Edit/EditCloseEvent.h
    Edit/EditCloseEvent.cpp
    Edit/EditDoneEvent.h
    Edit/EditDoneEvent.cpp
    Edit/ResetShortCutEvent.h
    Edit/ResetShortCutEvent.cpp

    Export/ExportSearchEvent.h
    Export/ExportSearchEvent.cpp
    Export/ExportEvent.h
    Export/ExportEvent.cpp
    Export/ExportCloseEvent.h
    Export/ExportCloseEvent.cpp
    Export/ExportFileEvent.h
    Export/ExportFileEvent.cpp

    Import/ImportSearchEvent.h
    Import/ImportSearchEvent.cpp
    Import/ImportEvent.h
    Import/ImportEvent.cpp
    Import/ImportCloseEvent.h
    Import/ImportCloseEvent.cpp
    Import/ImportFileEvent.h
    Import/ImportFileEvent.cpp

    Main/ClearEvent.h
    Main/ClearEvent.cpp
    Main/InsertEvent.h
    Main/InsertEvent.cpp
    Main/LoadEvent.h
    Main/LoadEvent.cpp
    Main/SlotEvent.h
    Main/SlotEvent.cpp
    Main/HelpEvent.h
    Main/HelpEvent.cpp
    Main/AutoCopyEvent.h
    Main/AutoCopyEvent.cpp

    ShortCutsMenu/ExpandEvent.h
    ShortCutsMenu/ExpandEvent.cpp
    ShortCutsMenu/SearchEvent.h
    ShortCutsMenu/SearchEvent.cpp
    ShortCutsMenu/CopyEvent.h
    ShortCutsMenu/CopyEvent.cpp
    ShortCutsMenu/PasteEvent.h
    ShortCutsMenu/PasteEvent.cpp
)

# Set include directories
target_include_directories(Events 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}  # For local includes
    PRIVATE
        ${CMAKE_SOURCE_DIR}  # To allow includes relative to project root
)

# Link dependencies
target_link_libraries(Events 
    PUBLIC 
        RmlUi::RmlUi
    PRIVATE 
        ClipboardLogic
        ProjectUtils
        ViewModels
)