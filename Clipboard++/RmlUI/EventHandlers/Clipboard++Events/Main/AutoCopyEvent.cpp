#include "AutoCopyEvent.h"
#include <ClipboardListener.h>

bool AutoCopyEvent::m_isOn = false;

AutoCopyEvent::AutoCopyEvent(MemoryCellManager* memoryCellManager) : m_memoryCellManager(memoryCellManager) {
    ClipboardListener::Instance()->AddBaseCallback([this](const std::string text) {
        if(m_isOn)
            m_memoryCellManager->moveContentsOneDown();
    });
}

void AutoCopyEvent::handle(Rml::Event* event, Rml::StringList values) {
    m_isOn = !m_isOn;
}

bool AutoCopyEvent::isOn() {
    return m_isOn && true;
}