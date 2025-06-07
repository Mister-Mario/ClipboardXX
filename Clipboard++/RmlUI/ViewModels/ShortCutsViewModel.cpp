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
    if(viewIndex != 2) 
        viewIndex += 1;
    else {
        if(cellsIndex != m_memoryCellsShortCuts.size() - 1)
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
    for(const int& match : matches) {
        m_memoryCellsShortCuts.push_back(m_memoryCellsManager->getMemoryCell(match));
    }
    viewIndex = 0;
    cellsIndex = 0;
}

ClipboardInterface* ShortCutsViewModel::getMemoryCell(size_t i) {
    if(i >= m_memoryCellsShortCuts.size())
        return nullptr;
    return m_memoryCellsShortCuts.at(i);
}

int ShortCutsViewModel::getSelectedCell() {
    return viewIndex;
}