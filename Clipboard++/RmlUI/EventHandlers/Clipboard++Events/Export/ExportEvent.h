#ifndef EXPORT_EVENT_H
#define EXPORT_EVENT_H

#include "Clipboard++Event.h"

class ExportEvent : public ClipboardEvent {
public:
    explicit ExportEvent();
    virtual ~ExportEvent() = default;
    
    void handle(Rml::Event& event, Rml::StringList values) override;
};

#endif