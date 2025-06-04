#ifdef _WIN32

#ifndef KEY_SHORT_CUT_H
#define KEY_SHORT_CUT_H

#include <windows.h>
#include <string>
#include <functional>
#include "MemoryCells/MemoryCell.h"

class KeyShortCut {
    public:
        KeyShortCut(int id_offset, UINT fsModifiers, UINT vk);
        ~KeyShortCut();

        bool registerKeyShortCut();
        bool unregisterKeyShortCut();
    private:
        int m_id;
        UINT m_fsModifiers;
        UINT m_vk;
};

#endif
#endif