#include "InsertEvent.h"

InsertEvent::InsertEvent(MemoryCellManager* memoryCellManager) : m_memoryCellManager(memoryCellManager) {}

void InsertEvent::handle(Rml::Event* event, Rml::StringList values) {
    auto cell = m_memoryCellManager->getSelectedCell();
    Rml::String input = "";
    if (auto element = event->GetCurrentElement()->GetOwnerDocument()->GetElementById("input")){
        input = element->GetAttribute<Rml::String>("value", "");
        element->SetAttribute("value", "");
    }
    cell->setText(input); 
}