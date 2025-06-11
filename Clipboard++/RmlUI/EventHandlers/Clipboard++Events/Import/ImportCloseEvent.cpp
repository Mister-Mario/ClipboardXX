#include "ImportCloseEvent.h"
#include "../EventManager.h"

ImportCloseEvent::ImportCloseEvent() {}

void ImportCloseEvent::handle(Rml::Event& event, Rml::StringList values) {
    EventManager::ChangeDocument("main_window", "file_manager_import");
}