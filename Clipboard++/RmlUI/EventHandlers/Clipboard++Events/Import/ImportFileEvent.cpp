#include "ImportFileEvent.h"
#include "../EventManager.h"
#include "Utils/StringUtils.h"

/**
 * @brief Constructor for the ImportFileEvent.
 * @param memoryCellManager A pointer to the manager for clipboard memory cells.
 * @param fileManager A pointer to the file manager used to handle file operations.
 * @param translator A pointer to the translation manager for localized strings.
 */
ImportFileEvent::ImportFileEvent(MemoryCellManager* memoryCellManager, FileManager* fileManager, TranslationManager* translator) : m_memoryCellManager(memoryCellManager), m_fileManager(fileManager), m_translator(translator) {}

/**
 * @brief Handles the final step of the import process.
 * @details This function is triggered after the user has selected a file and is ready to import. It validates that
 * a delimiter has been provided and a file has been selected. If both are valid, it reads the file using the
 * specified delimiter, loads the contents into the memory cells, and switches the UI back to the main window.
 * @param event The RmlUi event that triggered this action, used to find UI elements.
 * @param values A list of string parameters (not used in this handler).
 */
void ImportFileEvent::handle(Rml::Event* event, Rml::StringList values) {
    if(auto delimiter = event->GetCurrentElement()->GetOwnerDocument()->GetElementById("delimiter_input")){
        Rml::String strDelimiter = delimiter->GetAttribute<Rml::String>("value", "");
        
        // Validate that a delimiter has been entered.
        if(strDelimiter.length() == 0){
            m_fileManager->showErrorDialog(m_translator->getString("file.dialog.message.delimiter").c_str());
            return;
        }

        // Validate that a file has been chosen via the file dialog.
        if(m_fileManager->getLastFile().length() == 0) {
            m_fileManager->showErrorDialog(m_translator->getString("file.dialog.message.import.search").c_str());
            return;
        }

        // Read the file, load the cells, and change the document view.
        m_memoryCellManager->loadCells(m_fileManager->readFile(m_fileManager->getLastFile().c_str(), StringUtils::getDelimiter(strDelimiter)));
        EventManager::ChangeDocument("main_window", "file_manager_import");
    }
}
