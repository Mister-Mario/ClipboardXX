#include <EditViewModel.h>

/**
 * @brief Provides access to the singleton instance of the EditViewModel.
 * @return EditViewModel* A pointer to the singleton instance.
 */
EditViewModel* EditViewModel::Instance() {
    static EditViewModel instance;
    return &instance;
}

/**
 * @brief Constructor for the EditViewModel.
 */
EditViewModel::EditViewModel() {}

/**
 * @brief Destructor for the EditViewModel.
 */
EditViewModel::~EditViewModel() {}

/**
 * @brief Registers a key as part of a new shortcut combination.
 * @details Adds the given key identifier to an internal list that represents
 * the new shortcut being defined by the user.
 * @param key The RmlUi key identifier to add to the new shortcut.
 */
void EditViewModel::RegisterKey(Rml::Input::KeyIdentifier key) {
    newShortCut.push_back(key);
}

/**
 * @brief Clears the currently defined new shortcut.
 * @details Resets the internal list of keys for the new shortcut,
 * effectively discarding any keys registered so far.
 */
void EditViewModel::ResetNewShortCut() {
    newShortCut.clear();
}

/**
 * @brief Gets the collection of keys for the new shortcut.
 * @return std::vector<Rml::Input::KeyIdentifier> A copy of the vector containing the keys
 * that make up the new shortcut.
 */
std::vector<Rml::Input::KeyIdentifier> EditViewModel::GetNewShortCut() const {
    return newShortCut;
}

/**
 * @brief Sets the shortcut that is currently selected for editing.
 * @param selectedShortCut A pointer to the KeyShortCut object to be edited.
 */
void EditViewModel::SetSelectedShortCut(KeyShortCut* selectedShortCut) {
    m_selectedShortCut = selectedShortCut;
}

/**
 * @brief Gets the shortcut that is currently selected for editing.
 * @return KeyShortCut* A pointer to the currently selected KeyShortCut object.
 */
KeyShortCut* EditViewModel::GetSelectedShortCut() {
    return m_selectedShortCut;
}
