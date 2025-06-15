#include "ImportEvent.h"
#include "../EventManager.h"

/**
 * @brief Constructor for the ImportEvent.
 */
ImportEvent::ImportEvent() {}

/**
 * @brief Handles the event to open the file import interface.
 * @details This function switches the visible RmlUi document from the main application window 
 * to the file import screen, allowing the user to begin the import process.
 * @param event The RmlUi event that triggered this action (not directly used).
 * @param values A list of string parameters (not used in this handler).
 */
void ImportEvent::handle(Rml::Event* event, Rml::StringList values) {
    EventManager::ChangeDocument("file_manager_import", "main_window");
}
