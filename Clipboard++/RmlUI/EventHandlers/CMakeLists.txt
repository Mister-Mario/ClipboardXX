add_library(EventHandlers STATIC
    EventListener.h
    EventListener.cpp
    EventListenerInstancer.h
    EventListenerInstancer.cpp
    EventManager.h
    EventManager.cpp
)

# Set include directories
target_include_directories(EventHandlers 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(EventHandlers PUBLIC RmlUi::RmlUi)