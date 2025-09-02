#ifndef EDIT_DONE_EVENT_H
#define EDIT_DONE_EVENT_H

#include "Clipboard++Event.h"
#include "ClipboardLogic/MemoryCells/MemoryCellManager.h"
#include <EditViewModel.h>
#include <KeyShortCuts/KeyShortCutManager.h>
#include <Utils/TranslationManager.h>
#include <Utils/FileManager.h>


class EditDoneEvent : public ClipboardEvent {
public:
    explicit EditDoneEvent(MemoryCellManager* memoryCellManager, KeyShortCutManager* keyShortCutsManager, EditViewModel* editViewModel, TranslationManager* translator, FileManager* fileManager);
    virtual ~EditDoneEvent() = default;
    
    void handle(Rml::Event* event, Rml::StringList values) override;
private:
    MemoryCellManager* m_memoryCellManager;
    EditViewModel* m_editViewModel;
    KeyShortCutManager* m_keyShortCutsManager;
    TranslationManager* m_translator;
    FileManager* m_fileManager;
};

#endif