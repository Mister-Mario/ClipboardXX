#ifndef PASTE_EVENT_H
#define PASTE_EVENT_H

#include "QClipboard/MemoryCells/MemoryCellManager.h"
#include "Clipboard++Event.h"
#include <windows.h>

class PasteEvent : public ClipboardEvent {
public:
    explicit PasteEvent(HWND lastWindow, MemoryCellManager* memoryCellManager);
    virtual ~PasteEvent() = default;
    
    void handle(Rml::Event* event, Rml::StringList values) override;
private:
    MemoryCellManager* m_memoryCellManager;
    HWND m_lastWindow;
    bool SimulatePaste();
};

#endif