#include <ShortCutsViewModel.h>

/**
 * @brief Provides access to the singleton instance of the ShortCutsViewModel.
 * @return ShortCutsViewModel* A pointer to the singleton instance.
 */
ShortCutsViewModel* ShortCutsViewModel::Instance() {
    static ShortCutsViewModel instance;
    return &instance;
}

/**
 * @brief Constructor for the ShortCutsViewModel.
 * @details Initializes member variables and gets an instance of the MemoryCellManager.
 */
ShortCutsViewModel::ShortCutsViewModel() : m_memoryCellsManager(MemoryCellManager::Instance()) {
    viewIndex = 0;
    cellsIndex = 0;
}

/**
 * @brief Destructor for the ShortCutsViewModel.
 */
ShortCutsViewModel::~ShortCutsViewModel() {}

/**
 * @brief Moves the selection index up in the view.
 * @details Decrements the view index. If the view index is already at the top,
 * it attempts to scroll the underlying list of cells up by decrementing the cell index.
 */
void ShortCutsViewModel::moveUpIndex() {
    if(viewIndex != 0)
        viewIndex -= 1;
    else {
        if(cellsIndex != 0)
            cellsIndex -= 1;
    }
}

/**
 * @brief Moves the selection index down in the view.
 * @details Increments the view index. If the view index is at the bottom,
 * it attempts to scroll the underlying list of cells down by incrementing the cell index.
 */
void ShortCutsViewModel::moveDownIndex() {
    if(viewIndex != 2){ // Assumes a fixed view size of 3
        if(viewIndex + 1 >= m_memoryCellsShortCuts.size())
            return; 
        viewIndex += 1;
    }
    else {
        if(cellsIndex != m_memoryCellsShortCuts.size() - 1 - 2) // -2 because view can hold 3
            cellsIndex += 1;
    }
}

/**
 * @brief Updates the list of shortcuts based on a search filter.
 * @details Filters the memory cells from the MemoryCellManager based on the search input.
 * An empty input string matches all cells. It then resets the view and cell indices.
 * @param searchInput The string to search for within the content of the memory cells.
 */
void ShortCutsViewModel::updateList(std::string searchInput) {
    std::vector<int> matches;
    std::vector<std::string> contents = m_memoryCellsManager->getContents();
    size_t size = contents.size();
    for (size_t i = 0; i < size; i++) {
        if (searchInput == "" || contents.at(i).find(searchInput) != std::string::npos) {
            matches.push_back(i);
        }
    }
    m_memoryCellsShortCuts.clear();
    m_selectedCellsIndexes.clear();
    for(const int& match : matches) {
        m_memoryCellsShortCuts.push_back(m_memoryCellsManager->getMemoryCell(match));
        m_selectedCellsIndexes.push_back(match);
    }
    viewIndex = 0;
    cellsIndex = 0;
}

/**
 * @brief Gets a memory cell currently visible in the view.
 * @param i The index within the visible part of the list (typically 0, 1, or 2).
 * @return ClipboardInterface* A pointer to the requested memory cell, or nullptr if the index is out of bounds.
 */
ClipboardInterface* ShortCutsViewModel::getMemoryCell(size_t i) {
    size_t index = i + cellsIndex;
    if(index >= m_memoryCellsShortCuts.size())
        return nullptr;
    return m_memoryCellsShortCuts.at(index);
}

/**
 * @brief Gets the currently selected item's index within the view.
 * @return int The relative index of the selected cell in the view (typically 0, 1, or 2).
 */
int ShortCutsViewModel::getSelectedCell() {
    return viewIndex;
}

/**
 * @brief Checks if there is any cell currently selected or available.
 * @return bool True if the list of shortcuts is not empty, false otherwise.
 */
bool ShortCutsViewModel::hasSelectedCell() {
    return m_memoryCellsShortCuts.size() != 0;
}

/**
 * @brief Gets the absolute index of the selected cell from the original manager list.
 * @return size_t The true index of the selected cell.
 */
size_t ShortCutsViewModel::getSelectedCellIndex() {
    return m_selectedCellsIndexes.at(viewIndex + cellsIndex);
}

/**
 * @brief Checks if there is any cell currently over the showed ones.
 * @return bool True if there is a cell over, false otherwise.
 */
bool ShortCutsViewModel::canMoveUp() {
    return cellsIndex != 0;
}

/**
 * @brief Checks if there is any cell under the showed ones.
 * @return bool True if there is a cell under, false otherwise.
 */
bool ShortCutsViewModel::canMoveDown() {
    int max =  m_memoryCellsShortCuts.size() - 1 - 2;
    return max > 0 && cellsIndex < max;
}