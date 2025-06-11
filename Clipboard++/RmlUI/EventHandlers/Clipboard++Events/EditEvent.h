#ifndef EDIT_EVENT_H
#define EDIT_EVENT_H

#include "Clipboard++Event.h"
#include "QClipboard/MemoryCells/MemoryCellManager.h"
#include "QClipboard/KeyShortCuts/KeyShortCutManager.h"

class EditEvent : public ClipboardEvent {
public:
    explicit EditEvent(MemoryCellManager* memoryCellManager, KeyShortCutManager* keyShortCutsManager);
    virtual ~EditEvent() = default;
    
    void handle(Rml::Event& event, Rml::StringList values) override;
private:
    MemoryCellManager* m_memoryCellManager;
    KeyShortCutManager* m_keyShortCutsManager
};

#endif