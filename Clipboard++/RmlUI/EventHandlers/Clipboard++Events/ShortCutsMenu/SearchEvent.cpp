#include "SearchEvent.h"

SearchEvent::SearchEvent(ShortCutsViewModel* shortCutsViewModel) : m_shortCutsViewModel(shortCutsViewModel) {}

void SearchEvent::handle(Rml::Event* event, Rml::StringList values) {
    if (auto element = event->GetCurrentElement()){ 
        m_shortCutsViewModel->updateList(element->GetAttribute<Rml::String>("value", ""));
    }
}