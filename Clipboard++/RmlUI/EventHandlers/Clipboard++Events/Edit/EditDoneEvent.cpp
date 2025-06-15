#include "EditDoneEvent.h"
#include "../EventManager.h"

/**
 * @brief Constructor for the EditDoneEvent.
 * @param memoryCellManager A pointer to the manager for clipboard memory cells.
 * @param keyShortCutsManager A pointer to the manager that handles global shortcut registration.
 * @param editViewModel A pointer to the view model that manages shortcut editing state.
 * @param translator A pointer to the translation manager for localized strings.
 * @param fileManager A pointer to the file manager, used here for showing dialogs.
 */
EditDoneEvent::EditDoneEvent(MemoryCellManager* memoryCellManager, KeyShortCutManager* keyShortCutsManager, EditViewModel* editViewModel, TranslationManager* translator, FileManager* fileManager) :
    m_memoryCellManager(memoryCellManager),
    m_keyShortCutsManager(keyShortCutsManager),
    m_editViewModel(editViewModel),
    m_translator(translator),
    m_fileManager(fileManager)
    {}

/**
 * @brief Handles the event to finalize the editing of a shortcut.
 * @details This function first validates that the user has defined a new shortcut. It then determines whether the
 * original shortcut was for 'copy' or 'paste' and updates the selected cell with the new key combination.
 * Finally, it triggers the global key shortcut manager to apply the changes and switches the UI back to the main window.
 * @param event The RmlUi event that triggered this action.
 * @param values A list of string parameters (not used in this handler).
 */
void EditDoneEvent::handle(Rml::Event* event, Rml::StringList values) {
    // Ensure the user has actually defined a new shortcut.
    if(m_editViewModel->GetNewShortCut().size() == 0) {
        m_fileManager->showErrorDialog(m_translator->getString("file.dialog.message.edit").c_str());
        return;
    }

    auto selectedCell = m_memoryCellManager->getSelectedCell();

    // Check if the shortcut being edited was the 'copy' shortcut and update it.
    if(selectedCell->getKeyShortCutCopy() == m_editViewModel->GetSelectedShortCut()){
        selectedCell->setKeyShortCutCopy(m_editViewModel->GetNewShortCut());
    }
    // Check if the shortcut being edited was the 'paste' shortcut and update it.
    if(selectedCell->getKeyShortCutPaste() == m_editViewModel->GetSelectedShortCut()) {
        selectedCell->setKeyShortCutPaste(m_editViewModel->GetNewShortCut());
    }

    // Apply the changes to the system's hotkey listener.
    m_keyShortCutsManager->ModifyKeyShortCuts(m_memoryCellManager);
    EventManager::ChangeDocument("main_window", "edit");
}
