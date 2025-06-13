#include <KeyShortCuts/KeyShortCutManager.h>
#include "Utils/FileManager.h"
#include "Utils/StringUtils.h"
#include <RmlUi/Core/Types.h>
#include <RmlUi/Core/StringUtilities.h>
#include <format>

KeyShortCutManager* KeyShortCutManager::m_instance = nullptr;

KeyShortCutManager::KeyShortCutManager(){
    m_shortcutsBase.push_back(new KeyShortCut("copy 0", {Rml::Input::KI_LCONTROL, Rml::Input::KI_C}));
    m_shortcutsBase.push_back(new KeyShortCut("paste 0", {Rml::Input::KI_LCONTROL, Rml::Input::KI_V}));
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
        m_shortcutsBase.push_back(GetShortCutFromString(shortcuts[i], std::format("copy {}", i/2 + 1)));
        m_shortcutsBase.push_back(GetShortCutFromString(shortcuts[i + 1], std::format("paste {}", i/2 + 1)));
    }
    m_shortcuts = GetBaseList();
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


KeyShortCut* KeyShortCutManager::GetCopyShortCut(size_t i) const {
    if(i * 2 < m_shortcuts.size())
        return m_shortcuts.at(i * 2);
    return nullptr;
}

KeyShortCut* KeyShortCutManager::GetPasteShortCut(size_t i) const{
    if((i * 2 + 1) < m_shortcuts.size())
        return m_shortcuts.at(i * 2 + 1);
    return nullptr;
}

std::vector<KeyShortCut*> KeyShortCutManager::GetBaseList() const {
    return m_shortcutsBase;
}

KeyShortCut* KeyShortCutManager::FilterShortCuts(Rml::Input::KeyIdentifier key) {
    if(key == lastKeyPressed)
        return nullptr;
    std::vector<KeyShortCut*> filtered = {};
    for(KeyShortCut* shortCut : m_shortcuts){
        if(keysFiltered < shortCut->getShortCut().size() && shortCut->getShortCut().at(keysFiltered) == key)
            filtered.push_back(shortCut);
    }

    if(filtered.size() > 1){
        keysFiltered += 1;
        m_shortcuts = filtered;
        lastKeyPressed = key;
        return nullptr;
    }
    else if(filtered.size() == 0) {
        lastKeyPressed = Rml::Input::KI_UNKNOWN;
        keysFiltered = 0;
        m_shortcuts = GetBaseList();
        return nullptr;
    }
    else { //(filtered.size() == 1)
        KeyShortCut* shortCut = filtered.at(0);
        keysFiltered += 1;
        if(shortCut->getShortCut().size() != keysFiltered){ //There is one but you need more keys
            lastKeyPressed = key;
            m_shortcuts = filtered;
            return nullptr;
        }
        else {  // Found
            lastKeyPressed = Rml::Input::KI_UNKNOWN;
            keysFiltered = 0;
            m_shortcuts = GetBaseList();
            return shortCut;
        }
    }
}

void KeyShortCutManager::ModifyKeyShortCut(KeyShortCut* keyShortCut, std::vector<Rml::Input::KeyIdentifier> newShortCut) {
    keyShortCut->setShortCut(newShortCut);
    for(size_t i = 0; i < m_shortcutsBase.size(); i+=1)
        if(m_shortcutsBase.at(i) == keyShortCut)
            m_shortcutsBase.at(i)->setShortCut(newShortCut);
    m_shortcuts = GetBaseList();
    WriteShortCuts();
}

void KeyShortCutManager::WriteShortCuts() {
    std::vector<std::string> shortCuts = {};
    for(size_t i = 2; i < m_shortcutsBase.size(); i+=1) {
        shortCuts.push_back(m_shortcutsBase.at(i)->toString());
    }
    FileManager::Instance()->exportFile("assets/conf/shortCuts.csv", ';', shortCuts, false);
}