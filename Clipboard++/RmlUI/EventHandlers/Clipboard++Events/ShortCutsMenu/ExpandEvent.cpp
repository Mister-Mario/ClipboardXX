#include "ExpandEvent.h"
#include "../EventManager.h"
#include <RmlUi_Backend.h>

/**
 * @brief Constructor for the ExpandEvent.
 * @param memoryCellManager A pointer to the manager for clipboard memory cells.
 * @param shortCutsViewModel A pointer to the view model that manages the shortcuts list.
 */
ExpandEvent::ExpandEvent(MemoryCellManager* memoryCellManager, ShortCutsViewModel* shortCutsViewModel) : m_memoryCellManager(memoryCellManager), m_shortCutsViewModel(shortCutsViewModel) {}

/**
 * @brief Handles the event to expand from the shortcuts menu to the main application view.
 * @details This function sets the currently highlighted shortcut as the active one,
 * adjusts the main window's appearance (enables border, maximizes), and then
 * switches the visible RmlUi document from the shortcuts menu to the main window.
 * @param event The RmlUi event that triggered this action.
 * @param values A list of string parameters.
 */
void ExpandEvent::handle(Rml::Event* event, Rml::StringList values) {
    if(m_shortCutsViewModel->hasSelectedCell())
        m_memoryCellManager->setSelectedCell(m_shortCutsViewModel->getSelectedCellIndex());
    
    Backend::SetBorder(true);
    Backend::MaximizeWindow();
    EventManager::ChangeDocument("main_window", "shortcuts_menu");
}
