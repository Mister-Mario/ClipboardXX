#include <ShortCutsViewModel.h>

ShortCutsViewModel* ShortCutsViewModel::Instance() {
    static ShortCutsViewModel instance;
    return &instance;
}

ShortCutsViewModel::ShortCutsViewModel() : m_memoryCellsManager(MemoryCellManager::Instance()) {
    viewIndex = 0;
    cellsIndex = 0;
}

ShortCutsViewModel::~ShortCutsViewModel() {}

void ShortCutsViewModel::moveUpIndex() {
    if(viewIndex != 0)
        viewIndex -= 1;
    else {
        if(cellsIndex != 0)
            cellsIndex -= 1;
    }
}

void ShortCutsViewModel::moveDownIndex() {
    if(viewIndex != 2){
        if(viewIndex + 1 >= m_memoryCellsShortCuts.size())
            return; 
        viewIndex += 1;
    }
    else {
        if(cellsIndex != m_memoryCellsShortCuts.size() - 1 - 2) // -2 cause view can hold 3
            cellsIndex += 1;
    }
}

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

ClipboardInterface* ShortCutsViewModel::getMemoryCell(size_t i) {
    size_t index = i + cellsIndex;
    if(index >= m_memoryCellsShortCuts.size())
        return nullptr;
    return m_memoryCellsShortCuts.at(index);
}

int ShortCutsViewModel::getSelectedCell() {
    return viewIndex;
}

bool ShortCutsViewModel::hasSelectedCell() {
    return m_memoryCellsShortCuts.size() != 0;
}

size_t ShortCutsViewModel::getSelectedCellIndex() {
    return m_selectedCellsIndexes.at(viewIndex + cellsIndex);
}