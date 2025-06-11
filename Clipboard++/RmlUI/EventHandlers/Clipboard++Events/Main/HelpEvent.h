#ifndef HELP_EVENT_H
#define HELP_EVENT_H

#include "QClipboard/MemoryCells/MemoryCellManager.h"
#include "Clipboard++Event.h"
#include "Utils/LinkManager.h"

class HelpEvent : public ClipboardEvent {
public:
    explicit HelpEvent();
    virtual ~HelpEvent() = default;
    
    void handle(Rml::Event& event, Rml::StringList values) override;
};

#endif