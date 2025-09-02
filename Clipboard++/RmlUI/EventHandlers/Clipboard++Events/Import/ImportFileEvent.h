#ifndef IMPORT_FILE_EVENT_H
#define IMPORT_FILE_EVENT_H

#include "ClipboardLogic/MemoryCells/MemoryCellManager.h"
#include "Utils/FileManager.h"
#include "Utils/TranslationManager.h"
#include "Utils/StringUtils.h"
#include "Clipboard++Event.h"

class ImportFileEvent : public ClipboardEvent {
public:
    explicit ImportFileEvent(MemoryCellManager* memoryCellManager, FileManager* fileManager, TranslationManager* translator);
    virtual ~ImportFileEvent() = default;
    
    void handle(Rml::Event* event, Rml::StringList values) override;
private:
    MemoryCellManager* m_memoryCellManager;
    FileManager* m_fileManager;
    TranslationManager* m_translator;
};

#endif