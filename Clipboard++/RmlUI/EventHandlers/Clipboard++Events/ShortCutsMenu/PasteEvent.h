#ifndef PASTE_EVENT_H
#define PASTE_EVENT_H

#include "QClipboard/MemoryCells/MemoryCellManager.h"
#include "WindowFocusEvent.h"
#include <windows.h>

class PasteEvent : public WindowFocusEvent {
public:
    explicit PasteEvent(HWND lastWindow, MemoryCellManager* memoryCellManager);
    virtual ~PasteEvent() = default;
protected:
    void DoHandle(Rml::Event* event, Rml::StringList values) override;
private:
    MemoryCellManager* m_memoryCellManager;
    HWND m_lastWindow;
    bool SimulatePaste();
};

#endif