#include "MemoryCell.h"

/**
 * @brief Constructor for the MemoryCell.
 * @param name A unique name or identifier for this cell.
 * @param keyShortCutPaste A pointer to the KeyShortCut object for the paste operation.
 * @param keyShortCutCopy A pointer to the KeyShortCut object for the copy operation.
 */
MemoryCell::MemoryCell(std::string name, KeyShortCut* keyShortCutPaste, KeyShortCut* keyShortCutCopy) :
    m_text(""), 
    m_name(name),
    m_keyShortCutPaste(keyShortCutPaste),
    m_keyShortCutCopy(keyShortCutCopy)
{}

/**
 * @brief Sets the text content of this memory cell.
 * @param text The string to store in the cell.
 */
void MemoryCell::setText(const std::string& text) {
    m_text = text;
}

/**
 * @brief Gets the text content of this memory cell.
 * @return std::string The text currently stored in the cell.
 */
std::string MemoryCell::text() const {
    return m_text;
}

/**
 * @brief Gets the name of this memory cell.
 * @return std::string The name/identifier of the cell.
 */
std::string MemoryCell::name() const {
    return m_name;
}

/**
 * @brief Clears the text content of the cell, setting it to an empty string.
 */
void MemoryCell::clear() {
    m_text = "";
}

/**
 * @brief Gets the key shortcut associated with the paste action for this cell.
 * @return KeyShortCut* A pointer to the paste shortcut object.
 */
KeyShortCut* MemoryCell::getKeyShortCutPaste() {
    return m_keyShortCutPaste;
}

/**
 * @brief Gets the key shortcut associated with the copy action for this cell.
 * @return KeyShortCut* A pointer to the copy shortcut object.
 */
KeyShortCut* MemoryCell::getKeyShortCutCopy() {
    return m_keyShortCutCopy;
}

/**
 * @brief Sets a new key combination for this cell's paste shortcut.
 * @param newShortCut A vector of keys representing the new shortcut.
 */
void MemoryCell::setKeyShortCutPaste(std::vector<Rml::Input::KeyIdentifier> newShortCut) {
    m_keyShortCutPaste->setShortCut(newShortCut);
}

/**
 * @brief Sets a new key combination for this cell's copy shortcut.
 * @param newShortCut A vector of keys representing the new shortcut.
 */
void MemoryCell::setKeyShortCutCopy(std::vector<Rml::Input::KeyIdentifier> newShortCut) {
    m_keyShortCutCopy->setShortCut(newShortCut);
}
