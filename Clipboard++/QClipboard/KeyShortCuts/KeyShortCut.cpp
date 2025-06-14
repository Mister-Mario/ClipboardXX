#include "KeyShortCut.h"
#include <StringUtils.h>
#include <TranslationManager.h>
#include <format>

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

bool KeyShortCut::operator==(const KeyShortCut& other) const {
    return this->m_event == other.m_event;
}

std::string KeyShortCut::toString() {
    return toString(m_shortCutCombination);
}

std::string KeyShortCut::toString(std::vector<Rml::Input::KeyIdentifier> shortCutCombination) {
    TranslationManager* translator = TranslationManager::Instance(); 
    std::string content = "";
    for(auto key : shortCutCombination){
        content.append(translator->getString(std::format("keys.{}", StringUtils::getStringFronEnum(key)))).append("+");
    }
    return content.substr(0, content.length() - 1);
}