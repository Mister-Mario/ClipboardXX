#ifndef RESET_SHORT_CUT_EVENT_H
#define RESET_SHORT_CUT_EVENT_H

#include "Clipboard++Event.h"
#include <EditViewModel.h>

class ResetShortCutEvent : public ClipboardEvent {
public:
    explicit ResetShortCutEvent(EditViewModel* editViewModel);
    virtual ~ResetShortCutEvent() = default;
    
    void handle(Rml::Event* event, Rml::StringList values) override;
private:
    EditViewModel* m_editViewModel;
};

#endif