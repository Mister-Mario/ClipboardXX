#ifndef IMPORT_EVENT_H
#define IMPORT_EVENT_H

#include "Clipboard++Event.h"

class ImportEvent : public ClipboardEvent {
public:
    explicit ImportEvent();
    virtual ~ImportEvent() = default;
    
    void handle(Rml::Event* event, Rml::StringList values) override;
};

#endif