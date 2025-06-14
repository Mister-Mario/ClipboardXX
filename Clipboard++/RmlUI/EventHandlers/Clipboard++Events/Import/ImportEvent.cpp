#include "ImportEvent.h"
#include "../EventManager.h"

ImportEvent::ImportEvent() {}

void ImportEvent::handle(Rml::Event* event, Rml::StringList values) {
    EventManager::ChangeDocument("file_manager_import", "main_window");
}