#include "KeyShortCut.h"
#include "Utils/StringUtils.h"
#include "Utils/TranslationManager.h"
#include <format>

/**
 * @brief Constructor for the KeyShortCut class.
 * @param event The event string that this shortcut will trigger (e.g., "copy 1").
 * @param shortCutCombination A vector of RmlUi key identifiers that make up the shortcut.
 */
KeyShortCut::KeyShortCut(std::string event, std::vector<Rml::Input::KeyIdentifier> shortCutCombination): 
    m_event(event),
    m_shortCutCombination(shortCutCombination)
{}

/**
 * @brief Gets the key combination for this shortcut.
 * @return std::vector<Rml::Input::KeyIdentifier> The vector of keys for the shortcut.
 */
std::vector<Rml::Input::KeyIdentifier> KeyShortCut::getShortCut() const {
    return m_shortCutCombination;
}

/**
 * @brief Sets a new key combination for this shortcut.
 * @param newCombination The new vector of keys for the shortcut.
 */
void KeyShortCut::setShortCut(const std::vector<Rml::Input::KeyIdentifier>& newCombination) {
    m_shortCutCombination = newCombination;
}

/**
 * @brief Gets the event string associated with this shortcut.
 * @return std::string The event string (e.g., "copy 1").
 */
std::string KeyShortCut::getEvent() const {
    return m_event;
}

/**
 * @brief Equality operator overload.
 * @details Compares two KeyShortCut objects based on their event string.
 * @param other The other KeyShortCut object to compare against.
 * @return bool True if the event strings are identical, false otherwise.
 */
bool KeyShortCut::operator==(const KeyShortCut& other) const {
    return this->m_event == other.m_event;
}

/**
 * @brief Converts a given shortcut combination to a human-readable string.
 * @details Iterates through the keys, gets their localized string representation,
 * and joins them with a '+' character.
 * @param shortCutCombination The vector of keys to convert.
 * @return std::string A string representation of the provided shortcut.
 */
std::string KeyShortCut::toStringTranslated(std::vector<Rml::Input::KeyIdentifier> shortCutCombination) {
    TranslationManager* translator = TranslationManager::Instance(); 
    std::string content = "";
    for(auto key : shortCutCombination){
        content.append(translator->getString(std::format("keys.{}", StringUtils::getStringFronEnum(key)))).append("+");
    }
    // Remove the trailing '+'
    return content.substr(0, content.length() - 1);
}

/**
 * @brief Converts this shortcut to string.
 * @details Iterates through the keys and joins them with a '+' character.
 * @return std::string A string representation of the provided shortcut.
 */
std::string KeyShortCut::toString() {
    std::string content = "";
    for(auto key : m_shortCutCombination){
        content.append(StringUtils::getStringFronEnum(key)).append("+");
    }
    // Remove the trailing '+'
    return content.substr(0, content.length() - 1);
}
