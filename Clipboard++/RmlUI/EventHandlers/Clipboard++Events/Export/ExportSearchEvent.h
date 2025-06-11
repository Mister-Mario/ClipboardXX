#ifndef EXPORT_SEARCH_EVENT_H
#define EXPORT_SEARCH_EVENT_H

#include "Utils/FileManager.h"
#include "Utils/TranslationManager.h"
#include "Clipboard++Event.h"

class ExportSearchEvent : public ClipboardEvent {
public:
    explicit ExportSearchEvent(FileManager* fileManager, TranslationManager* translator);
    virtual ~ExportSearchEvent() = default;
    
    void handle(Rml::Event& event, Rml::StringList values) override;
private:
    FileManager* m_fileManager;
    TranslationManager* m_translator;
};

#endif