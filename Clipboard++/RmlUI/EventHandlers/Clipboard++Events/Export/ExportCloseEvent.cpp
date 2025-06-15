#include "ExportCloseEvent.h"
#include "../EventManager.h"

/**
 * @brief Constructor for the ExportCloseEvent.
 */
ExportCloseEvent::ExportCloseEvent() {}

/**
 * @brief Handles the event to close the file export interface and return to the main window.
 * @details This function switches the visible RmlUi document from the file export screen
 * back to the main application window, typically canceling the export process.
 * @param event The RmlUi event that triggered this action (not directly used).
 * @param values A list of string parameters (not used in this handler).
 */
void ExportCloseEvent::handle(Rml::Event* event, Rml::StringList values) {
    EventManager::ChangeDocument("main_window", "file_manager_export");
}
