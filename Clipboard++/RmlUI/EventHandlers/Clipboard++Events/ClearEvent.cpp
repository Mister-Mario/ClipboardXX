#include "ClearEvent.h"

ClearEvent::ClearEvent(MemoryCellManager* memoryCellManager) : m_memoryCellManager(memoryCellManager) {}

void ClearEvent::handle(Rml::Event& event, Rml::StringList values) {
    m_memoryCellManager->getSelectedCell()->clear();
}