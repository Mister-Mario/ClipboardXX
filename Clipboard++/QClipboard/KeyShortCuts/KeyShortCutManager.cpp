#include <KeyShortCuts/KeyShortCutManager.h>
#include "Utils/FileManager.h"
#include "Utils/StringUtils.h"
#include <RmlUi/Core/Types.h>
#include <RmlUi/Core/StringUtilities.h>
#include <format>

// Initialize the static singleton instance to nullptr.
KeyShortCutManager* KeyShortCutManager::m_instance = nullptr;

/**
 * @brief Private constructor for the KeyShortCutManager.
 * @details Initializes the base shortcuts for system-wide copy/paste
 * and then loads custom shortcuts from a file.
 */
KeyShortCutManager::KeyShortCutManager(){
    m_shortcutsBase.push_back(new KeyShortCut("copy 0", {Rml::Input::KI_LCONTROL, Rml::Input::KI_C}));
    m_shortcutsBase.push_back(new KeyShortCut("paste 0", {Rml::Input::KI_LCONTROL, Rml::Input::KI_V}));
    LoadKeyShortCuts();
}

/**
 * @brief Provides access to the singleton instance of the KeyShortCutManager.
 * @return KeyShortCutManager* A pointer to the singleton instance.
 */
KeyShortCutManager* KeyShortCutManager::Instance() {
    if(m_instance == nullptr) {
        m_instance = new KeyShortCutManager();
    }
    return m_instance;
}

/**
 * @brief Loads custom key shortcuts from a configuration file.
 * @details Reads shortcuts from 'shortCuts.csv' and parses them, adding them to the base list.
 * The format is expected to be two lines per memory cell (copy, then paste).
 */
void KeyShortCutManager::LoadKeyShortCuts() {
    auto shortcuts = SelectFile();
    size_t size = shortcuts.size() == 0 ? 0 : shortcuts.size() - 1;
    for(size_t i = 0; i < size; i+= 2){
        m_shortcutsBase.push_back(GetShortCutFromString(shortcuts[i], std::format("copy {}", i/2 + 1)));
        m_shortcutsBase.push_back(GetShortCutFromString(shortcuts[i + 1], std::format("paste {}", i/2 + 1)));
    }
    m_shortcuts = GetBaseList();
}

/**
 * @brief Selects the appropriate shortcut file to load.
 * @details It reads both a user-modifiable shortcut file and a base/default file. If the sizes
 * differ (indicating a potential corruption or mismatch), it returns the base file's content as a fallback.
 * @return std::vector<std::string> A list of strings, each representing a shortcut definition.
 */
std::vector<std::string> KeyShortCutManager::SelectFile() {
    FileManager* fileManager = FileManager::Instance();
    auto shortcuts = fileManager->readFile("assets/conf/shortCuts.csv", ';', false);
    auto baseShortcuts = fileManager->readFile("assets/conf/shortCutsBase.csv", ';', false);
    return shortcuts.size() != baseShortcuts.size() ? baseShortcuts : shortcuts;
}

/**
 * @brief Parses a string and converts it into a KeyShortCut object.
 * @param shortcut The string representation of the shortcut (e.g., "KI_LCONTROL+KI_C").
 * @param event The event string to associate with this shortcut (e.g., "copy 1").
 * @return KeyShortCut* A new KeyShortCut object.
 */
KeyShortCut* KeyShortCutManager::GetShortCutFromString(std::string shortcut, std::string event) {
    Rml::StringList shortcutExpanded;
    Rml::StringUtilities::ExpandString(shortcutExpanded, shortcut, '+');
    std::vector<Rml::Input::KeyIdentifier> rmlKeys = {};
    for(auto key : shortcutExpanded) {
        rmlKeys.push_back(StringUtils::getEnumFronString(key));
    }

    return new KeyShortCut(event, rmlKeys);
}

/**
 * @brief Gets the 'copy' shortcut for a specific memory cell index.
 * @param i The index of the memory cell.
 * @return KeyShortCut* A pointer to the corresponding copy shortcut, or nullptr if out of bounds.
 */
KeyShortCut* KeyShortCutManager::GetCopyShortCut(size_t i) const {
    if(i * 2 < m_shortcuts.size())
        return m_shortcuts.at(i * 2);
    return nullptr;
}

/**
 * @brief Gets the 'paste' shortcut for a specific memory cell index.
 * @param i The index of the memory cell.
 * @return KeyShortCut* A pointer to the corresponding paste shortcut, or nullptr if out of bounds.
 */
KeyShortCut* KeyShortCutManager::GetPasteShortCut(size_t i) const{
    if((i * 2 + 1) < m_shortcuts.size())
        return m_shortcuts.at(i * 2 + 1);
    return nullptr;
}

/**
 * @brief Gets the complete list of all loaded base shortcuts.
 * @return std::vector<KeyShortCut*> A copy of the base shortcuts list.
 */
std::vector<KeyShortCut*> KeyShortCutManager::GetBaseList() const {
    return m_shortcutsBase;
}

/**
 * @brief Filters the active shortcuts list based on a key press.
 * @details This function implements the logic for detecting multi-key shortcuts. It maintains
 * an internal state of possible shortcuts and narrows them down with each key press.
 * @param key The key identifier that was just pressed.
 * @return KeyShortCut* A pointer to the completed shortcut if a sequence is finalized, otherwise nullptr.
 */
KeyShortCut* KeyShortCutManager::FilterShortCuts(Rml::Input::KeyIdentifier key) {
    if(key == lastKeyPressed)
        return nullptr;
    
    std::vector<KeyShortCut*> filtered = {};
    for(KeyShortCut* shortCut : m_shortcuts){
        if(keysFiltered < shortCut->getShortCut().size() && shortCut->getShortCut().at(keysFiltered) == key)
            filtered.push_back(shortCut);
    }

    if(filtered.size() > 1){
        // Multiple possibilities remain, wait for the next key.
        keysFiltered += 1;
        m_shortcuts = filtered;
        lastKeyPressed = key;
        return nullptr;
    }
    else if(filtered.size() == 0) {
        // No match found, reset the filter state.
        lastKeyPressed = Rml::Input::KI_UNKNOWN;
        keysFiltered = 0;
        m_shortcuts = GetBaseList();
        return nullptr;
    }
    else { //(filtered.size() == 1)
        KeyShortCut* shortCut = filtered.at(0);
        keysFiltered += 1;
        if(shortCut->getShortCut().size() != keysFiltered){
            // One possibility remains, but it requires more keys.
            lastKeyPressed = key;
            m_shortcuts = filtered;
            return nullptr;
        }
        else {
            // Shortcut sequence completed. Reset state and return the found shortcut.
            lastKeyPressed = Rml::Input::KI_UNKNOWN;
            keysFiltered = 0;
            m_shortcuts = GetBaseList();
            return shortCut;
        }
    }
}

/**
 * @brief Modifies the shortcut list based on changes from the MemoryCellManager and saves them.
 * @param memoryCellManager The manager containing the potentially updated memory cells and their shortcuts.
 */
void KeyShortCutManager::ModifyKeyShortCuts(MemoryCellManager* memoryCellManager) {
    m_shortcutsBase.clear();
    for(size_t i = 0; i < memoryCellManager->getMemoryCellCount(); i+= 1){
        auto cell = memoryCellManager->getMemoryCell(i);
        m_shortcutsBase.push_back(cell->getKeyShortCutCopy());
        m_shortcutsBase.push_back(cell->getKeyShortCutPaste());
    }
    m_shortcuts = GetBaseList();
    WriteShortCuts();
}

/**
 * @brief Writes the current custom shortcuts to the configuration file.
 * @details It skips the first two base shortcuts (system copy/paste) and writes the rest
 * to 'shortCuts.csv' for persistence.
 */
void KeyShortCutManager::WriteShortCuts() {
    std::vector<std::string> shortCuts = {};
    for(size_t i = 2; i < m_shortcutsBase.size(); i+=1) {
        shortCuts.push_back(m_shortcutsBase.at(i)->toString());
    }
    FileManager::Instance()->exportFile("assets/conf/shortCuts.csv", ';', shortCuts, false);
}
