#include "ResetShortCutEvent.h"
#include "../EventManager.h"

ResetShortCutEvent::ResetShortCutEvent(EditViewModel* editViewModel) : m_editViewModel(editViewModel) {}

void ResetShortCutEvent::handle(Rml::Event* event, Rml::StringList values) {
    m_editViewModel->ResetNewShortCut();
}