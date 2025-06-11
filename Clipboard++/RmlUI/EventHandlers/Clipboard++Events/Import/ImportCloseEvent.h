#ifndef IMPORT_CLOSE_EVENT_H
#define IMPORT_CLOSE_EVENT_H

#include "Clipboard++Event.h"

class ImportCloseEvent : public ClipboardEvent {
public:
    explicit ImportCloseEvent();
    virtual ~ImportCloseEvent() = default;
    
    void handle(Rml::Event* event, Rml::StringList values) override;
};

#endif