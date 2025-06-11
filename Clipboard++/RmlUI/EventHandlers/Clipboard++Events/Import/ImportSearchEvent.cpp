#include "ImportSearchEvent.h"

ImportSearchEvent::ImportSearchEvent(FileManager* fileManager, TranslationManager* translator) : m_fileManager(fileManager), m_translator(translator) {}

void ImportSearchEvent::handle(Rml::Event& event, Rml::StringList values) {
    m_fileManager->searchImportFile(m_translator->getString("file.dialog.title.import").c_str());
}