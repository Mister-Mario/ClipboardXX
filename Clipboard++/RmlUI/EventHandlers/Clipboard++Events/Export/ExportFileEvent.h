#ifndef EXPORT_FILE_EVENT_H
#define EXPORT_FILE_EVENT_H

#include "QClipboard/MemoryCells/MemoryCellManager.h"
#include "Utils/FileManager.h"
#include "Utils/TranslationManager.h"
#include "Utils/StringUtils.h"
#include "Clipboard++Event.h"

class ExportFileEvent : public ClipboardEvent {
public:
    explicit ExportFileEvent(MemoryCellManager* memoryCellManager, FileManager* fileManager, TranslationManager* translator);
    virtual ~ExportFileEvent() = default;
    
    void handle(Rml::Event* event, Rml::StringList values) override;
private:
    MemoryCellManager* m_memoryCellManager;
    FileManager* m_fileManager;
    TranslationManager* m_translator;
};

#endif