#ifndef EDIT_EVENT_H
#define EDIT_EVENT_H

#include "Clipboard++Event.h"
#include "ClipboardLogic/MemoryCells/MemoryCellManager.h"
#include <EditViewModel.h>

class EditEvent : public ClipboardEvent {
public:
    explicit EditEvent(MemoryCellManager* memoryCellManager, EditViewModel* editViewModel);
    virtual ~EditEvent() = default;
    
    void handle(Rml::Event* event, Rml::StringList values) override;
private:
    MemoryCellManager* m_memoryCellManager;
    EditViewModel* m_editViewModel;
};

#endif