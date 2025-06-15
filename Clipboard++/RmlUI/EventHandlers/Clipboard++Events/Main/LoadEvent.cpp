#include "LoadEvent.h"

/**
 * @brief Constructor for the LoadEvent.
 * @param memoryCellManager A pointer to the manager for clipboard memory cells.
 */
LoadEvent::LoadEvent(MemoryCellManager* memoryCellManager) : m_memoryCellManager(memoryCellManager) {}

/**
 * @brief Handles the event to load the content of a selected cell into the main clipboard slot.
 * @details This action effectively copies the text from the currently selected memory cell 
 * into cell 0, which represents the system's active clipboard.
 * @param event The RmlUi event that triggered this action (not directly used).
 * @param values A list of string parameters (not used in this handler).
 */
void LoadEvent::handle(Rml::Event* event, Rml::StringList values) {
    m_memoryCellManager->getMemoryCell(0)->setText(m_memoryCellManager->getSelectedCell()->text());
}
