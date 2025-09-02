#ifndef COPY_EVENT_H
#define COPY_EVENT_H

#include "ClipboardLogic/MemoryCells/MemoryCellManager.h"
#include "WindowFocusEvent.h"
#include <windows.h>

class CopyEvent :  public WindowFocusEvent {
public:
    explicit CopyEvent(MemoryCellManager* memoryCellManager);
    virtual ~CopyEvent() = default;
    
protected:
    void DoHandle(Rml::Event* event, Rml::StringList values) override;
private:
    MemoryCellManager* m_memoryCellManager;
    bool SimulateCopy();
};

#endif