#ifndef COPY_EVENT_H
#define COPY_EVENT_H

#include "QClipboard/MemoryCells/MemoryCellManager.h"
#include "Clipboard++Event.h"
#include <windows.h>

class CopyEvent : public ClipboardEvent {
public:
    explicit CopyEvent(HWND lastWindow, MemoryCellManager* memoryCellManager);
    virtual ~CopyEvent() = default;
    
    void handle(Rml::Event& event, Rml::StringList values) override;
private:
    MemoryCellManager* m_memoryCellManager;
    HWND m_lastWindow;
    bool SimulateCopy();
};

#endif