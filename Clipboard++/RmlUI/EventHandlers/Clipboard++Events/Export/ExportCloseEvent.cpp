#include "ExportCloseEvent.h"
#include "../EventManager.h"

ExportCloseEvent::ExportCloseEvent() {}

void ExportCloseEvent::handle(Rml::Event* event, Rml::StringList values) {
    EventManager::ChangeDocument("main_window", "file_manager_export");
}