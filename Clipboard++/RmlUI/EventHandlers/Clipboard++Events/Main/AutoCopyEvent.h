#ifndef AUTO_COPY_EVENT_H
#define AUTO_COPY_EVENT_H

#include "Clipboard++Event.h"
#include <MemoryCells/MemoryCellManager.h>

class AutoCopyEvent : public ClipboardEvent {
public:
    explicit AutoCopyEvent(MemoryCellManager* memoryCellManager);
    virtual ~AutoCopyEvent() = default;
    
    void handle(Rml::Event* event, Rml::StringList values) override;
    static bool isOn();
private:
    MemoryCellManager* m_memoryCellManager;
    static bool m_isOn;
};

#endif