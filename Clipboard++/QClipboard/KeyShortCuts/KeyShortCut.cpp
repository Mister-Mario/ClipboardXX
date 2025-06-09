#include "KeyShortCut.h"
#include "Utils/FileManager.h"
#include "MemoryCells/MemoryCell.h"

KeyShortCut::KeyShortCut(std::string event, std::vector<Rml::Input::KeyIdentifier> shortCutCombination): 
    m_event(event),
    m_shortCutCombination(shortCutCombination)
{}

std::vector<Rml::Input::KeyIdentifier> KeyShortCut::getShortCut() const {
    return m_shortCutCombination;
}

void KeyShortCut::setShortCut(const std::vector<Rml::Input::KeyIdentifier>& newCombination) {
    m_shortCutCombination = newCombination;
}

std::string KeyShortCut::getEvent() const {
    return m_event;
}