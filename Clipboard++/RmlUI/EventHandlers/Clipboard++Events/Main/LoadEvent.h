#ifndef LOAD_EVENT_H
#define LOAD_EVENT_H

#include "QClipboard/MemoryCells/MemoryCellManager.h"
#include "Clipboard++Event.h"

class LoadEvent : public ClipboardEvent {
public:
    explicit LoadEvent(MemoryCellManager* memoryCellManager);
    virtual ~LoadEvent() = default;
    
    void handle(Rml::Event* event, Rml::StringList values) override;
private:
    MemoryCellManager* m_memoryCellManager;
};

#endif