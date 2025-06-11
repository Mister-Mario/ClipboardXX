#ifndef INSERT_EVENT_H
#define INSERT_EVENT_H

#include "QClipboard/MemoryCells/MemoryCellManager.h"
#include "Clipboard++Event.h"

class InsertEvent : public ClipboardEvent {
public:
    explicit InsertEvent(MemoryCellManager* memoryCellManager);
    virtual ~InsertEvent() = default;
    
    void handle(Rml::Event& event, Rml::StringList values) override;
private:
    MemoryCellManager* m_memoryCellManager;
};

#endif