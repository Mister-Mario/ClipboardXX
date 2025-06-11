#include "EditEvent.h"
#include "../EventManager.h"

EditEvent::EditEvent(MemoryCellManager* memoryCellManager,KeyShortCutManager* keyShortCutsManager) : m_memoryCellManager(memoryCellManager), m_keyShortCutsManager(keyShortCutsManager){}

void EditEvent::handle(Rml::Event& event, Rml::StringList values) {
    if(values[1] == "paste")
        m_keyShortCutsManager->SetSelectedShortCut(m_memoryCellManager->getSelectedCell()->getKeyShortCutPaste());
    else //copy
         m_keyShortCutsManager->SetSelectedShortCut(m_memoryCellManager->getSelectedCell()->getKeyShortCutCopy());
    EventManager::ChangeDocument("edit", "main_window");
}