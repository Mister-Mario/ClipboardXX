#include "ClipboardAdapter.h"


/**
 * @brief Constructor for the ClipboardAdapter.
 * @param clipboard A pointer to the Qt clipboard object this adapter will wrap.
 * @param keyShortCutPaste A pointer to the KeyShortCut object for the paste operation.
 * @param keyShortCutCopy A pointer to the KeyShortCut object for the copy operation.
 */
ClipboardAdapter::ClipboardAdapter(QClipboard* clipboard, KeyShortCut* keyShortCutPaste, KeyShortCut* keyShortCutCopy) :
    m_clipboard(clipboard),
    m_keyShortCutPaste(keyShortCutPaste),
    m_keyShortCutCopy(keyShortCutCopy)
{}

/**
 * @brief Sets the text content of the system clipboard.
 * @param text The string to place onto the clipboard.
 */
void ClipboardAdapter::setText(const std::string& text) {
    m_clipboard->setText(QString::fromStdString(text));
}

/**
 * @brief Gets the current text content from the system clipboard.
 * @return std::string The text currently on the clipboard.
 */
std::string ClipboardAdapter::text() const {
    return m_clipboard->text().toStdString();
}

/**
 * @brief Gets the name of this clipboard interface implementation.
 * @return std::string The constant name "clipboard".
 */
std::string ClipboardAdapter::name() const {
    return "clipboard";
}

/**
 * @brief Clears the content of the system clipboard.
 */
void ClipboardAdapter::clear() {
    m_clipboard->clear();
}

/**
 * @brief Gets the key shortcut associated with the paste action for this cell.
 * @return KeyShortCut* A pointer to the paste shortcut object.
 */
KeyShortCut* ClipboardAdapter::getKeyShortCutPaste() {
    return m_keyShortCutPaste;
}

/**
 * @brief Gets the key shortcut associated with the copy action for this cell.
 * @return KeyShortCut* A pointer to the copy shortcut object.
 */
KeyShortCut* ClipboardAdapter::getKeyShortCutCopy() {
    return m_keyShortCutCopy;
}

/**
 * @brief Sets a new key combination for the paste shortcut.
 * @note This function is currently not implemented.
 * @param newShortCut A vector of keys representing the new shortcut.
 */
void ClipboardAdapter::setKeyShortCutPaste(std::vector<Rml::Input::KeyIdentifier> newShortCut) {
}

/**
 * @brief Sets a new key combination for the copy shortcut.
 * @note This function is currently not implemented.
 * @param newShortCut A vector of keys representing the new shortcut.
 */
void ClipboardAdapter::setKeyShortCutCopy(std::vector<Rml::Input::KeyIdentifier> newShortCut) {
}
