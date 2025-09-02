#ifndef CLEAR_EVENT_H
#define CLEAR_EVENT_H

#include "ClipboardLogic/MemoryCells/MemoryCellManager.h"
#include "Clipboard++Event.h"

class ClearEvent : public ClipboardEvent {
public:
    explicit ClearEvent(MemoryCellManager* memoryCellManager);
    virtual ~ClearEvent() = default;
    
    void handle(Rml::Event* event, Rml::StringList values) override;
private:
    MemoryCellManager* m_memoryCellManager;
};

#endif