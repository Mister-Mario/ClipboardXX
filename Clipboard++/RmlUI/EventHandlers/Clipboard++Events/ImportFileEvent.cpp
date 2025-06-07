#include "ImportFileEvent.h"
#include "../EventManager.h"

ImportFileEvent::ImportFileEvent(MemoryCellManager* memoryCellManager, FileManager* fileManager, TranslationManager* translator) : m_memoryCellManager(memoryCellManager), m_fileManager(fileManager), m_translator(translator) {}

void ImportFileEvent::handle(Rml::Event& event, Rml::StringList values) {
        if(auto delimiter = event.GetCurrentElement()->GetOwnerDocument()->GetElementById("delimiter_input")){
        Rml::String strDelimiter = delimiter->GetAttribute<Rml::String>("value", "");
        if(strDelimiter.length() == 0){
            m_fileManager->showErrorDialog(m_translator->getString("file.dialog.message.delimiter").c_str());
            return;
        }

        if(m_fileManager->getLastFile().length() == 0) {
            m_fileManager->showErrorDialog(m_translator->getString("file.dialog.message.import.search").c_str());
            return;
        }

        m_memoryCellManager->loadCells(m_fileManager->readFile(m_fileManager->getLastFile().c_str(), StringUtils::getDelimiter(strDelimiter)));
        EventManager::ChangeDocument("shortcuts_menu", "file_manager_import");
    }
}