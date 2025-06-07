#ifndef SEARCH_EVENT_H
#define SEARCH_EVENT_H

#include "QClipboard/MemoryCells/MemoryCellManager.h"
#include "Clipboard++Event.h"
#include <ShortCutsViewModel.h>

class SearchEvent : public ClipboardEvent {
public:
    explicit SearchEvent(ShortCutsViewModel* shortCutsViewModel);
    virtual ~SearchEvent() = default;
    
    void handle(Rml::Event& event, Rml::StringList values) override;
private:
    ShortCutsViewModel* m_shortCutsViewModel;
};

#endif