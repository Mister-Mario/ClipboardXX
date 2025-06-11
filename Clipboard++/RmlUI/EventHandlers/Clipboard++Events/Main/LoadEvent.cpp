#include "LoadEvent.h"

LoadEvent::LoadEvent(MemoryCellManager* memoryCellManager) : m_memoryCellManager(memoryCellManager) {}

void LoadEvent::handle(Rml::Event* event, Rml::StringList values) {
    m_memoryCellManager->getMemoryCell(0)->setText(m_memoryCellManager->getSelectedCell()->text());
}