#ifndef KEY_SHORT_CUT_MANAGER_H
#define KEY_SHORT_CUT_MANAGER_H

#include "MemoryCellManager.h"

class KeyShortCutManager {
    public:
        static KeyShortCutManager* Instance();
    protected:
        KeyShortCutManager();
    private:
        static KeyShortCutManager* m_instance;
        static MemoryCellManager* m_memoryCellManager;
};

#endif