#ifndef MEMORY_CELL_MANAGER_H
#define MEMORY_CELL_MANAGER_H

#include <ClipboardInterface.h>
#include <ClipboardAdapter.h>
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
    protected:
        MemoryCellManager();
    private:
        static MemoryCellManager* m_instance;
        std::vector<std::unique_ptr<ClipboardInterface>> m_memoryCells;
};

#endif