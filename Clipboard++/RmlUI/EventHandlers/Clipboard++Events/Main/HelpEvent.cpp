#include "HelpEvent.h"

HelpEvent::HelpEvent() {}

void HelpEvent::handle(Rml::Event& event, Rml::StringList values) {
    openHelp();
}