#ifndef SLOT_EVENT_H
#define SLOT_EVENT_H

#include "ClipboardLogic/MemoryCells/MemoryCellManager.h"
#include "Clipboard++Event.h"

class SlotEvent : public ClipboardEvent {
public:
    explicit SlotEvent(MemoryCellManager* memoryCellManager);
    virtual ~SlotEvent() = default;
    
    void handle(Rml::Event* event, Rml::StringList values) override;
private:
    MemoryCellManager* m_memoryCellManager;
};

#endif