#include "ExportEvent.h"
#include "../EventManager.h"

/**
 * @brief Constructor for the ExportEvent.
 */
ExportEvent::ExportEvent() {}

/**
 * @brief Handles the event to open the file export interface.
 * @details This function switches the visible RmlUi document from the main application window
 * to the file export screen, allowing the user to begin the export process.
 * @param event The RmlUi event that triggered this action (not directly used).
 * @param values A list of string parameters (not used in this handler).
 */
void ExportEvent::handle(Rml::Event* event, Rml::StringList values) {
    EventManager::ChangeDocument("file_manager_export", "main_window");
}
