#include "InsertEvent.h"

/**
 * @brief Constructor for the InsertEvent.
 * @param memoryCellManager A pointer to the manager for clipboard memory cells.
 */
InsertEvent::InsertEvent(MemoryCellManager* memoryCellManager) : m_memoryCellManager(memoryCellManager) {}

/**
 * @brief Handles the event to insert text from an input field into the selected memory cell.
 * @details This function retrieves the currently selected cell. It then finds an element with the ID 'input'
 * in the document, gets its 'value', clears the input field, and sets the retrieved text into the selected cell.
 * @param event The RmlUi event that triggered this action, used to find the source document.
 * @param values A list of string parameters (not used in this handler).
 */
void InsertEvent::handle(Rml::Event* event, Rml::StringList values) {
    auto cell = m_memoryCellManager->getSelectedCell();
    Rml::String input = "";
    if (auto element = event->GetCurrentElement()->GetOwnerDocument()->GetElementById("input")){
        input = element->GetAttribute<Rml::String>("value", "");
        element->SetAttribute("value", "");
    }
    cell->setText(input); 
}
