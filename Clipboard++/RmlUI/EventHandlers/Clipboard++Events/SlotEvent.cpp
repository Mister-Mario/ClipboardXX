#include "SlotEvent.h"

SlotEvent::SlotEvent(MemoryCellManager* memoryCellManager) : m_memoryCellManager(memoryCellManager) {}

void SlotEvent::handle(Rml::Event& event, Rml::StringList values) {
    m_memoryCellManager->setSelectedCell(std::stoi(values[1]));
}