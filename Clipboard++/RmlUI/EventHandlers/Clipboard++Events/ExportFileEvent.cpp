#include "ExportFileEvent.h"
#include "../EventManager.h"

ExportFileEvent::ExportFileEvent(MemoryCellManager* memoryCellManager, FileManager* fileManager, TranslationManager* translator) : m_memoryCellManager(memoryCellManager), m_fileManager(fileManager), m_translator(translator) {}

void ExportFileEvent::handle(Rml::Event& event, Rml::StringList values) {
    if(auto delimiter = event.GetCurrentElement()->GetOwnerDocument()->GetElementById("delimiter_input")){
        Rml::String strDelimiter = delimiter->GetAttribute<Rml::String>("value", "");
        if(strDelimiter.length() == 0){
            m_fileManager->showErrorDialog(m_translator->getString("file.dialog.message.delimiter").c_str());
            return;
        }

        if(m_fileManager->getLastFile().length() == 0) {
            m_fileManager->showErrorDialog(m_translator->getString("file.dialog.message.export.search").c_str());
            return;
        }

        m_fileManager->exportFile(m_fileManager->getLastFile().c_str(), Utils::getDelimiter(strDelimiter), m_memoryCellManager->getContents());
        EventManager::ChangeDocument("main_window", "file_manager_export"); 
    }
}