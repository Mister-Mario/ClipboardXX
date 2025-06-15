#include "ImportCloseEvent.h"
#include "../EventManager.h"
/**
 * @brief Constructor for the ImportCloseEvent.
 */
ImportCloseEvent::ImportCloseEvent() {}

/**
 * @brief Handles the event to close the file import interface.
 * @details This function switches the visible RmlUi document from the file import screen
 * to the main application window.
 * @param event The RmlUi event that triggered this action (not directly used).
 * @param values A list of string parameters (not used in this handler).
 */
void ImportCloseEvent::handle(Rml::Event* event, Rml::StringList values) {
    EventManager::ChangeDocument("main_window", "file_manager_import");
}