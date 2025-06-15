#include "ExportFileEvent.h"
#include "../EventManager.h"
#include "Utils/StringUtils.h"

/**
 * @brief Constructor for the ExportFileEvent.
 * @param memoryCellManager A pointer to the manager for clipboard memory cells.
 * @param fileManager A pointer to the file manager used to handle file operations.
 * @param translator A pointer to the translation manager for localized strings.
 */
ExportFileEvent::ExportFileEvent(MemoryCellManager* memoryCellManager, FileManager* fileManager, TranslationManager* translator) : m_memoryCellManager(memoryCellManager), m_fileManager(fileManager), m_translator(translator) {}

/**
 * @brief Handles the final step of the export process.
 * @details This function is triggered after the user has specified a file name and is ready to export. It validates
 * that a delimiter has been provided and a file path has been set. If both are valid, it retrieves all memory cell
 * contents, exports them to the specified file, and switches the UI back to the main window.
 * @param event The RmlUi event that triggered this action, used to find UI elements.
 * @param values A list of string parameters (not used in this handler).
 */
void ExportFileEvent::handle(Rml::Event* event, Rml::StringList values) {
    if(auto delimiter = event->GetCurrentElement()->GetOwnerDocument()->GetElementById("delimiter_input")){
        Rml::String strDelimiter = delimiter->GetAttribute<Rml::String>("value", "");
        
        // Validate that a delimiter has been entered.
        if(strDelimiter.length() == 0){
            m_fileManager->showErrorDialog(m_translator->getString("file.dialog.message.delimiter").c_str());
            return;
        }

        // Validate that a file has been chosen via the file dialog.
        if(m_fileManager->getLastFile().length() == 0) {
            m_fileManager->showErrorDialog(m_translator->getString("file.dialog.message.export.search").c_str());
            return;
        }

        // Export the file and switch the document view.
        m_fileManager->exportFile(m_fileManager->getLastFile().c_str(), StringUtils::getDelimiter(strDelimiter), m_memoryCellManager->getContents());
        EventManager::ChangeDocument("main_window", "file_manager_export"); 
    }
}
