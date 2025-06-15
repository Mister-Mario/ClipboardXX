#include "AutoCopyEvent.h"
#include <ClipboardListener.h>

// Initialize the static flag to false by default.
bool AutoCopyEvent::m_isOn = false;

/**
 * @brief Constructor for the AutoCopyEvent.
 * @details Sets up a permanent base callback on the ClipboardListener. When the auto-copy feature is active,
 * this callback will automatically shift the existing clipboard history down to make room for the new item
 * whenever a new copy action is detected system-wide.
 * @param memoryCellManager A pointer to the manager for clipboard memory cells.
 */
AutoCopyEvent::AutoCopyEvent(MemoryCellManager* memoryCellManager) : m_memoryCellManager(memoryCellManager) {
    ClipboardListener::Instance()->AddBaseCallback([this](const std::string text) {
        if(m_isOn)
            m_memoryCellManager->moveContentsOneDown();
    });
}

/**
 * @brief Handles the event to toggle the auto-copy feature.
 * @details This function is typically connected to a UI button or switch. It inverts the
 * state of the `m_isOn` flag, effectively turning the auto-copy functionality on or off.
 * @param event The RmlUi event that triggered this action (not directly used).
 * @param values A list of string parameters (not used in this handler).
 */
void AutoCopyEvent::handle(Rml::Event* event, Rml::StringList values) {
    m_isOn = !m_isOn;
}

/**
 * @brief Checks if the auto-copy feature is currently enabled.
 * @return bool True if auto-copy is on, false otherwise.
 */
bool AutoCopyEvent::isOn() {
    return m_isOn;
}
