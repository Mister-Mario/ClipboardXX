#include "ExportEvent.h"
#include "../EventManager.h"

ExportEvent::ExportEvent() {}

void ExportEvent::handle(Rml::Event& event, Rml::StringList values) {
    EventManager::ChangeDocument("file_manager_export", "main_window");
}