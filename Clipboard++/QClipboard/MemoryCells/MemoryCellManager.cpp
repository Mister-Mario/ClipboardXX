#include "MemoryCellManager.h"
#include "MemoryCell.h"
#include <format>
#include "../KeyShortCuts/KeyShortCutManager.h"

// Get a singleton instance of the KeyShortCutManager.
KeyShortCutManager* keyShortCutManager = KeyShortCutManager::Instance();

/**
 * @brief Private constructor for the MemoryCellManager to enforce the singleton pattern.
 */
MemoryCellManager::MemoryCellManager(){}

/**
 * @brief Provides access to the singleton instance of the MemoryCellManager.
 * @return MemoryCellManager* A pointer to the singleton instance.
 */
MemoryCellManager* MemoryCellManager::Instance() {
    static MemoryCellManager instance;
    return &instance;
}

/**
 * @brief Gets the total number of memory cells currently managed.
 * @return size_t The number of cells.
 */
size_t MemoryCellManager::getMemoryCellCount() const {
    return m_memoryCells.size();
}

/**
 * @brief Retrieves a specific memory cell by its index.
 * @param index The index of the memory cell to retrieve.
 * @return ClipboardInterface* A pointer to the cell, or nullptr if the index is out of bounds.
 */
ClipboardInterface* MemoryCellManager::getMemoryCell(size_t index) {
    if (index < m_memoryCells.size()) {
        return m_memoryCells[index].get();
    }
    return nullptr;
}

/**
 * @brief Creates and adds a new, empty memory cell to the manager.
 * @details The new cell is automatically associated with the next available copy and paste shortcuts.
 * @return size_t The index of the newly created cell.
 */
size_t MemoryCellManager::addMemoryCell() {
    // Create the new memory cell
    auto newCell = std::make_unique<MemoryCell>(std::format("cell_{}", m_memoryCells.size()),
        keyShortCutManager->GetPasteShortCut(m_memoryCells.size()),
        keyShortCutManager->GetCopyShortCut(m_memoryCells.size()));
    
    // Add to collection
    m_memoryCells.push_back(std::move(newCell));
    return m_memoryCells.size() - 1;  // Return the index
}

/**
 * @brief Initializes the manager with a primary clipboard and a set number of memory cells.
 * @param clipboard A pointer to the ClipboardAdapter representing the system clipboard. This will be cell 0.
 * @param initialCells The total number of cells to create (including the system clipboard).
 */
void MemoryCellManager::initialize(ClipboardAdapter* clipboard, size_t initialCells) {
    // Reserve space for efficiency
    m_memoryCells.reserve(initialCells);
    
    // First space is always for the actual clipboard
    m_memoryCells.push_back(std::unique_ptr<ClipboardInterface>(clipboard));

    // Create initial memory cells
    for (size_t i = 1; i < initialCells; i++) {
        addMemoryCell();
    }
}

/**
 * @brief Clears all memory cells, releasing their resources.
 */
void MemoryCellManager::cleanup() {
    m_memoryCells.clear();
}

/**
 * @brief Sets the index of the currently active memory cell.
 * @param index The index to set as the selected one.
 */
void MemoryCellManager::setSelectedCell(size_t index) {
    this->selectedCell = index;
}

/**
 * @brief Gets a pointer to the currently selected memory cell.
 * @return ClipboardInterface* A pointer to the active cell.
 */
ClipboardInterface* MemoryCellManager::getSelectedCell() {
    return m_memoryCells[selectedCell].get();
}

/**
 * @brief Loads content into the memory cells from a vector of strings.
 * @details Populates cells sequentially from the start of the vector.
 * @param information A vector of strings to load into the cells.
 */
void MemoryCellManager::loadCells(std::vector<std::string> information){
    int sizeCells = m_memoryCells.size();
    int sizeInformation = information.size();
    for(int i = 0; i < sizeCells && i < sizeInformation; i++) {
        m_memoryCells[i].get()->setText(information[i]);
    }
}

/**
 * @brief Retrieves the text content from all managed cells.
 * @return std::vector<std::string> A vector containing the text from each cell.
 */
std::vector<std::string> MemoryCellManager::getContents() {
    std::vector<std::string> contents = {};
    int sizeCells = m_memoryCells.size();
    for(int i = 0; i < sizeCells; i++){
        contents.push_back(m_memoryCells[i].get()->text());
    }
    return contents;
}

/**
 * @brief Shifts the content of each memory cell down by one position.
 * @details This is used for the auto-copy feature, where the content of cell 0 moves to cell 1,
 * cell 1 to cell 2, and so on, to make room for a new entry in cell 0.
 */
void MemoryCellManager::moveContentsOneDown() {
    // Iterate backwards to avoid overwriting data before it's moved.
    int sizeCells = m_memoryCells.size() - 2;
    for(int i = sizeCells; i >= 0; i--){
        m_memoryCells.at(i + 1).get()->setText(m_memoryCells.at(i).get()->text());
    }
}
