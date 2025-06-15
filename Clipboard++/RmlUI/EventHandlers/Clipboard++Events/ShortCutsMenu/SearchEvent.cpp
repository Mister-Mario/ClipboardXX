#include "SearchEvent.h"

/**
 * @brief Constructor for the SearchEvent.
 * @param shortCutsViewModel A pointer to the view model that manages the shortcuts list.
 */
SearchEvent::SearchEvent(ShortCutsViewModel* shortCutsViewModel) : m_shortCutsViewModel(shortCutsViewModel) {}

/**
 * @brief Handles the search event triggered from the UI.
 * @details Retrieves the search term from the 'value' attribute of the source element
 * and calls the view model to update the list of shortcuts based on that term.
 * @param event The RmlUi event that triggered this action, used to get the source element.
 * @param values A list of string parameters (not used in this handler).
 */
void SearchEvent::handle(Rml::Event* event, Rml::StringList values) {
    if (auto element = event->GetCurrentElement()){ 
        m_shortCutsViewModel->updateList(element->GetAttribute<Rml::String>("value", ""));
    }
}
