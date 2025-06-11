#include "EditCloseEvent.h"
#include "../EventManager.h"

EditCloseEvent::EditCloseEvent() {}

void EditCloseEvent::handle(Rml::Event& event, Rml::StringList values) {
    EventManager::ChangeDocument("main_window", "edit");
}