#include "MemoryCellManager.h"
#include "MemoryCell.h"
#include <format>
#include "../KeyShortCuts/KeyShortCutManager.h"

KeyShortCutManager* keyShortCutManager = KeyShortCutManager::Instance();

MemoryCellManager::MemoryCellManager(){}

MemoryCellManager* MemoryCellManager::Instance() {
    static MemoryCellManager instance;
    return &instance;
}

size_t MemoryCellManager::getMemoryCellCount() const {
    return m_memoryCells.size();
}

ClipboardInterface* MemoryCellManager::getMemoryCell(size_t index) {
    if (index < m_memoryCells.size()) {
        return m_memoryCells[index].get();
    }
    return nullptr;
}

size_t MemoryCellManager::addMemoryCell() {
    // Create the new memory cell
    auto newCell = std::make_unique<MemoryCell>(std::format("cell_{}", m_memoryCells.size()),
        keyShortCutManager->GetPasteShortCut(m_memoryCells.size()),
        keyShortCutManager->GetCopyShortCut(m_memoryCells.size()));
    
    // Add to collection
    m_memoryCells.push_back(std::move(newCell));
    return m_memoryCells.size() - 1;  // Return the index
}

void MemoryCellManager::initialize(ClipboardAdapter* clipboard, size_t initialCells) {
    // Reserve space for efficiency
    m_memoryCells.reserve(initialCells);
    
    // First space is always for the actual clipboard
    m_memoryCells.push_back(std::unique_ptr<ClipboardInterface>(clipboard));

    // Create initial cells
    for (size_t i = 1; i < initialCells; i++) {
        addMemoryCell();
    }
}

void MemoryCellManager::cleanup() {
    m_memoryCells.clear();
}

void MemoryCellManager::setSelectedCell(size_t index) {
    this->selectedCell = index;
}

ClipboardInterface* MemoryCellManager::getSelectedCell() {
    return m_memoryCells[selectedCell].get();
}

void MemoryCellManager::loadCells(std::vector<std::string> information){
    int sizeCells = m_memoryCells.size();
    int sizeInformation = information.size();
    for(int i = 0; i < sizeCells && i < sizeInformation; i++) {
        m_memoryCells[i].get()->setText(information[i]);
    }
}

std::vector<std::string> MemoryCellManager::getContents() {
    std::vector<std::string> contents = {};
    int sizeCells = m_memoryCells.size();
    for(int i = 0; i < sizeCells; i++){
        contents.push_back(m_memoryCells[i].get()->text());
    }
    return contents;
}