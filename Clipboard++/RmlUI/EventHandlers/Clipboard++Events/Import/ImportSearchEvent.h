#ifndef IMPORT_SEARCH_EVENT_H
#define IMPORT_SEARCH_EVENT_H

#include "Utils/FileManager.h"
#include "Utils/TranslationManager.h"
#include "Clipboard++Event.h"

class ImportSearchEvent : public ClipboardEvent {
public:
    explicit ImportSearchEvent(FileManager* fileManager, TranslationManager* translator);
    virtual ~ImportSearchEvent() = default;
    
    void handle(Rml::Event& event, Rml::StringList values) override;
private:
    FileManager* m_fileManager;
    TranslationManager* m_translator;
};

#endif