#include "ClearEvent.h"

/**
 * @brief Constructor for the ClearEvent.
 * @param memoryCellManager A pointer to the manager for clipboard memory cells.
 */
ClearEvent::ClearEvent(MemoryCellManager* memoryCellManager) : m_memoryCellManager(memoryCellManager) {}

/**
 * @brief Handles the event to clear the content of the currently selected memory cell.
 * @param event The RmlUi event that triggered this action (not directly used).
 * @param values A list of string parameters (not used in this handler).
 */
void ClearEvent::handle(Rml::Event* event, Rml::StringList values) {
    m_memoryCellManager->getSelectedCell()->clear();
}
