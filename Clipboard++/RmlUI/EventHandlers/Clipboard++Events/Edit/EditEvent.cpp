#include "EditEvent.h"
#include "../EventManager.h"

EditEvent::EditEvent(MemoryCellManager* memoryCellManager,EditViewModel* editViewModel) : m_memoryCellManager(memoryCellManager), m_editViewModel(editViewModel){}

void EditEvent::handle(Rml::Event* event, Rml::StringList values) {
    if(values[1] == "paste"){
        m_editViewModel->SetSelectedShortCut(m_memoryCellManager->getSelectedCell()->getKeyShortCutPaste());
    }
    else{ //copy
        m_editViewModel->SetSelectedShortCut(m_memoryCellManager->getSelectedCell()->getKeyShortCutCopy());
    }
    m_editViewModel->ResetNewShortCut();
    EventManager::ChangeDocument("edit", "main_window");
}