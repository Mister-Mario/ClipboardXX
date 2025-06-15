#include "EditCloseEvent.h"
#include "../EventManager.h"

/**
 * @brief Constructor for the EditCloseEvent.
 */
EditCloseEvent::EditCloseEvent() {}

/**
 * @brief Handles the event to close the shortcut editing interface.
 * @details This function switches the visible RmlUi document from the shortcut editing screen
 * back to the main application window, effectively canceling the edit operation.
 * @param event The RmlUi event that triggered this action (not directly used).
 * @param values A list of string parameters (not used in this handler).
 */
void EditCloseEvent::handle(Rml::Event* event, Rml::StringList values) {
    EventManager::ChangeDocument("main_window", "edit");
}
