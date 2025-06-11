#ifndef CLIPBOARD_EVENT_H
#define CLIPBOARD_EVENT_H

#include <RmlUi/Core/Types.h>
#include <RmlUi/Core/ElementDocument.h>

class ClipboardEvent {
public:
    virtual ~ClipboardEvent() = default;
    virtual void handle(Rml::Event* event, Rml::StringList values) = 0;
};

#endif