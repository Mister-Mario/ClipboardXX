#ifndef EDIT_CLOSE_EVENT_H
#define EDIT_CLOSE_EVENT_H

#include "Clipboard++Event.h"

class EditCloseEvent : public ClipboardEvent {
public:
    explicit EditCloseEvent();
    virtual ~EditCloseEvent() = default;
    
    void handle(Rml::Event& event, Rml::StringList values) override;
};

#endif