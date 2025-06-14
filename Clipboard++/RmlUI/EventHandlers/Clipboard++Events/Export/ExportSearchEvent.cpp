#include "ExportSearchEvent.h"

ExportSearchEvent::ExportSearchEvent(FileManager* fileManager, TranslationManager* translator) : m_fileManager(fileManager), m_translator(translator) {}

void ExportSearchEvent::handle(Rml::Event* event, Rml::StringList values) {
    m_fileManager->searchExportFile(m_translator->getString("file.dialog.title.export").c_str());
}