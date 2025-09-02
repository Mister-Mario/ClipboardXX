#ifndef MEMORY_CELL_MANAGER_H
#define MEMORY_CELL_MANAGER_H

#include <Clipboard/ClipboardInterface.h>
#include <Clipboard/ClipboardAdapter.h>
#include <vector>
#include <memory>

class MemoryCellManager {
    public:
        static MemoryCellManager* Instance();
        size_t getMemoryCellCount() const;
        ClipboardInterface* getMemoryCell(size_t index);
        size_t addMemoryCell();
        void initialize(ClipboardAdapter* clipboard, size_t initialCells = 9);
        void cleanup();
        void setSelectedCell(size_t index);
        ClipboardInterface* getSelectedCell();
        void loadCells(std::vector<std::string> information);
        std::vector<std::string> getContents();
        void moveContentsOneDown();
    protected:
        MemoryCellManager();
    private:
        std::vector<std::unique_ptr<ClipboardInterface>> m_memoryCells;
        size_t selectedCell = 0;
};

#endif
