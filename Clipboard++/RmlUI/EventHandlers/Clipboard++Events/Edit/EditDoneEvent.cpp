#include "EditDoneEvent.h"
#include "../EventManager.h"

EditDoneEvent::EditDoneEvent(MemoryCellManager* memoryCellManager, KeyShortCutManager* keyShortCutsManager, EditViewModel* editViewModel, TranslationManager* translator, FileManager* fileManager) :
    m_memoryCellManager(memoryCellManager),
    m_keyShortCutsManager(keyShortCutsManager),
    m_editViewModel(editViewModel),
    m_translator(translator),
    m_fileManager(fileManager)
    {}

void EditDoneEvent::handle(Rml::Event& event, Rml::StringList values) {
    if(m_editViewModel->GetNewShortCut().size() == 0) {
        m_fileManager->showErrorDialog(m_translator->getString("file.dialog.message.edit").c_str());
        return;
    }
    auto selectedCell = m_memoryCellManager->getSelectedCell();
    if(selectedCell->getKeyShortCutCopy() == m_editViewModel->GetSelectedShortCut())
        m_keyShortCutsManager->ModifyKeyShortCut(selectedCell->getKeyShortCutCopy(), m_editViewModel->GetNewShortCut());
    if(selectedCell->getKeyShortCutPaste() == m_editViewModel->GetSelectedShortCut())
        m_keyShortCutsManager->ModifyKeyShortCut(selectedCell->getKeyShortCutPaste(), m_editViewModel->GetNewShortCut());
    EventManager::ChangeDocument("main_window", "edit");
}