#ifndef SHORTCUTS_VIEW_MODEL_H
#define SHORTCUTS_VIEW_MODEL_H

#include <ClipboardInterface.h>
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
    protected:
        ShortCutsViewModel();
        ~ShortCutsViewModel();
    private:
        MemoryCellManager* m_memoryCellsManager;
        int cellsIndex;
        int viewIndex;
        std::vector<ClipboardInterface*> m_memoryCellsShortCuts;
};

#endif