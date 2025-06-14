#ifndef EXPAND_EVENT_H
#define EXPAND_EVENT_H

#include "Clipboard++Event.h"
#include <MemoryCells/MemoryCellManager.h>
#include <ShortCutsViewModel.h>

class ExpandEvent : public ClipboardEvent {
public:
    explicit ExpandEvent(MemoryCellManager* memoryCellManager, ShortCutsViewModel* shortCutsViewModel);
    virtual ~ExpandEvent() = default;
    
    void handle(Rml::Event* event, Rml::StringList values) override;
private:
    int window_width;
    int window_height;
    MemoryCellManager* m_memoryCellManager; 
    ShortCutsViewModel* m_shortCutsViewModel; 
};

#endif