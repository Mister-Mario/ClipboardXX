#ifndef SHORTCUTS_VIEW_MODEL_H
#define SHORTCUTS_VIEW_MODEL_H

#include <Clipboard/ClipboardInterface.h>
#include <MemoryCells/MemoryCellManager.h>
#include <vector>

class ShortCutsViewModel {
    public:
        static ShortCutsViewModel* Instance();
        void updateList(std::string searchInput);
        void moveUpIndex();
        void moveDownIndex();
        ClipboardInterface* getMemoryCell(size_t i);
        int getSelectedCell();
        bool hasSelectedCell();
        size_t getSelectedCellIndex();
        bool canMoveUp();
        bool canMoveDown();
    protected:
        ShortCutsViewModel();
        ~ShortCutsViewModel();
    private:
        MemoryCellManager* m_memoryCellsManager;
        int cellsIndex;
        int viewIndex;
        std::vector<size_t> m_selectedCellsIndexes;
        std::vector<ClipboardInterface*> m_memoryCellsShortCuts;
};

#endif