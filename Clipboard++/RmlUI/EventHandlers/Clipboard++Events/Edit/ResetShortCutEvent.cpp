#include "ResetShortCutEvent.h"
#include "../EventManager.h"

/**
 * @brief Constructor for the ResetShortCutEvent.
 * @param editViewModel A pointer to the view model that manages shortcut editing.
 */
ResetShortCutEvent::ResetShortCutEvent(EditViewModel* editViewModel) : m_editViewModel(editViewModel) {}

/**
 * @brief Handles the event to reset the currently defined new shortcut.
 * @details This function calls the `ResetNewShortCut` method on the EditViewModel,
 * clearing any keys the user has entered while defining a new shortcut combination.
 * @param event The RmlUi event that triggered this action (not directly used).
 * @param values A list of string parameters (not used in this handler).
 */
void ResetShortCutEvent::handle(Rml::Event* event, Rml::StringList values) {
    m_editViewModel->ResetNewShortCut();
}
