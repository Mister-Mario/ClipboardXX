#ifndef EXPORT_CLOSE_EVENT_H
#define EXPORT_CLOSE_EVENT_H

#include "Clipboard++Event.h"

class ExportCloseEvent : public ClipboardEvent {
public:
    explicit ExportCloseEvent();
    virtual ~ExportCloseEvent() = default;
    
    void handle(Rml::Event* event, Rml::StringList values) override;
};

#endif