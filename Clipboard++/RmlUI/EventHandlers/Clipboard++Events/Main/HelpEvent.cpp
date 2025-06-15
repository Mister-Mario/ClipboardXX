#include "HelpEvent.h"

// Forward declaration for the function called by the handler.
void openHelp();

/**
 * @brief Constructor for the HelpEvent.
 */
HelpEvent::HelpEvent() {}

/**
 * @brief Handles the event to display help information.
 * @details This function calls the `openHelp()` function, which is expected
 * to open a help dialog, a web page, or some other form of user assistance.
 * @param event The RmlUi event that triggered this action (not directly used).
 * @param values A list of string parameters (not used in this handler).
 */
void HelpEvent::handle(Rml::Event* event, Rml::StringList values) {
    openHelp();
}
