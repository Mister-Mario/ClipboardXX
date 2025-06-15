#include "ImportSearchEvent.h"

/**
 * @brief Constructor for the ImportSearchEvent.
 * @param fileManager A pointer to the file manager used to handle file operations.
 * @param translator A pointer to the translation manager for localized strings.
 */
ImportSearchEvent::ImportSearchEvent(FileManager* fileManager, TranslationManager* translator) : m_fileManager(fileManager), m_translator(translator) {}

/**
 * @brief Handles the event to initiate a file search for import.
 * @details This function calls the file manager to open a system file dialog.
 * The title of the dialog is retrieved from the translation manager to support localization.
 * @param event The RmlUi event that triggered this action (not directly used).
 * @param values A list of string parameters (not used in this handler).
 */
void ImportSearchEvent::handle(Rml::Event* event, Rml::StringList values) {
    m_fileManager->searchImportFile(m_translator->getString("file.dialog.title.import").c_str());
}
