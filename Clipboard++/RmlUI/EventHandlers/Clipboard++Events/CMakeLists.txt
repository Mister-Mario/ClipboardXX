add_library(Events STATIC
    Clipboard++Event.h
    ClearEvent.h
    ClearEvent.cpp
    InsertEvent.h
    InsertEvent.cpp
    LoadEvent.h
    LoadEvent.cpp
    SlotEvent.h
    SlotEvent.cpp
    HelpEvent.h
    HelpEvent.cpp
    ImportSearchEvent.h
    ImportSearchEvent.cpp
    ImportEvent.h
    ImportEvent.cpp
    ImportCloseEvent.h
    ImportCloseEvent.cpp
    ImportFileEvent.h
    ImportFileEvent.cpp
    ExportSearchEvent.h
    ExportSearchEvent.cpp
    ExportEvent.h
    ExportEvent.cpp
    ExportCloseEvent.h
    ExportCloseEvent.cpp
    ExportFileEvent.h
    ExportFileEvent.cpp
    ExpandEvent.h
    ExpandEvent.cpp
    SearchEvent.h
    SearchEvent.cpp
    CopyEvent.h
    CopyEvent.cpp
    PasteEvent.h
    PasteEvent.cpp
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
        QClipboard
        ProjectUtils
        ViewModels
)