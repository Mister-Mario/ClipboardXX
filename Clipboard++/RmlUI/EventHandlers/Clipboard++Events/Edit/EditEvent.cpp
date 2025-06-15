#include "EditEvent.h"
#include "../EventManager.h"

/**
 * @brief Constructor for the EditEvent.
 * @param memoryCellManager A pointer to the manager for clipboard memory cells.
 * @param editViewModel A pointer to the view model that manages shortcut editing.
 */
EditEvent::EditEvent(MemoryCellManager* memoryCellManager,EditViewModel* editViewModel) : m_memoryCellManager(memoryCellManager), m_editViewModel(editViewModel){}

/**
 * @brief Handles the event to start editing a shortcut.
 * @details This function determines whether the user wants to edit the 'paste' or 'copy' shortcut based on the event parameters.
 * It sets the corresponding shortcut in the EditViewModel, resets any partially defined new shortcut, and then
 * switches the UI from the main window to the shortcut editing screen.
 * @param event The RmlUi event that triggered this action.
 * @param values A list of string parameters, where values[1] specifies the shortcut type ("paste" or "copy").
 */
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
