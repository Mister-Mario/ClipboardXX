#include "SlotEvent.h"

/**
 * @brief Constructor for the SlotEvent.
 * @param memoryCellManager A pointer to the manager for clipboard memory cells.
 */
SlotEvent::SlotEvent(MemoryCellManager* memoryCellManager) : m_memoryCellManager(memoryCellManager) {}

/**
 * @brief Handles the event to change the currently selected memory cell.
 * @details It reads an index from the event parameters and tells the MemoryCellManager 
 * to set the cell at that index as the active one.
 * @param event The RmlUi event that triggered this action (not directly used).
 * @param values A list of string parameters, where values[1] is expected to be the index of the cell to select.
 */
void SlotEvent::handle(Rml::Event* event, Rml::StringList values) {
    m_memoryCellManager->setSelectedCell(std::stoi(values[1]));
}
