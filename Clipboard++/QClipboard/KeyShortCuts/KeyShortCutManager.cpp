#include <KeyShortCuts/KeyShortCutManager.h>
#include "Utils/FileManager.h"
#include "Utils/StringUtils.h"
#include <RmlUi/Core/Types.h>
#include <RmlUi/Core/StringUtilities.h>
#include <format>

KeyShortCutManager* KeyShortCutManager::m_instance = nullptr;

KeyShortCutManager::KeyShortCutManager(){
    m_shortcuts.push_back(new KeyShortCut("paste 0", {Rml::Input::KI_LCONTROL, Rml::Input::KI_V}));
    m_shortcuts.push_back(new KeyShortCut("copy 0", {Rml::Input::KI_LCONTROL, Rml::Input::KI_C}));
    LoadKeyShortCuts();
}

KeyShortCutManager* KeyShortCutManager::Instance() {
    if(m_instance == nullptr) {
        m_instance = new KeyShortCutManager();
    }
    return m_instance;
}

void KeyShortCutManager::LoadKeyShortCuts() {
    auto shortcuts = SelectFile();
    size_t size = shortcuts.size() - 1;
    for(size_t i = 0; i < size; i+= 2){
        m_shortcuts.push_back(GetShortCutFromString(shortcuts[i], std::format("paste {}", i)));
        m_shortcuts.push_back(GetShortCutFromString(shortcuts[i + 1], std::format("copy {}", i)));
    }
}

std::vector<std::string> KeyShortCutManager::SelectFile() {
    FileManager* fileManager = FileManager::Instance();
    auto shortcuts = fileManager->readFile("assets/conf/shortCuts.csv", ';', false);
    auto baseShortcuts = fileManager->readFile("assets/conf/shortCutsBase.csv", ';', false);
    return shortcuts.size() != baseShortcuts.size() ? baseShortcuts : shortcuts;
}

KeyShortCut* KeyShortCutManager::GetShortCutFromString(std::string shortcut, std::string event) {
    Rml::StringList shortcutExpanded;
    Rml::StringUtilities::ExpandString(shortcutExpanded, shortcut, '+');
    std::vector<Rml::Input::KeyIdentifier> rmlKeys = {};
    for(auto key : shortcutExpanded) {
        rmlKeys.push_back(StringUtils::getEnumFronString(key));
    }

    return new KeyShortCut(event, rmlKeys);
}


KeyShortCut* KeyShortCutManager::GetPasteShortCut(size_t i) const {
    if(i * 2 < m_shortcuts.size())
        return m_shortcuts.at(i * 2);
    return nullptr;
}

KeyShortCut* KeyShortCutManager::GetCopyShortCut(size_t i) const{
    if((i * 2 + 1) < m_shortcuts.size())
        return m_shortcuts.at(i * 2 + 1);
    return nullptr;
}