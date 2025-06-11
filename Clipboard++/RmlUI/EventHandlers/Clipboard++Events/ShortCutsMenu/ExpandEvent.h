#ifndef EXPAND_EVENT_H
#define EXPAND_EVENT_H

#include "Clipboard++Event.h"

class ExpandEvent : public ClipboardEvent {
public:
    explicit ExpandEvent();
    virtual ~ExpandEvent() = default;
    
    void handle(Rml::Event& event, Rml::StringList values) override;
private:
    int window_width;
    int window_height;
};

#endif