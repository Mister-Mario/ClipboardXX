#ifndef KEY_SHORT_CUT_MANAGER_H
#define KEY_SHORT_CUT_MANAGER_H

#include "KeyShortCut.h"

class KeyShortCutManager {
    public:
        static KeyShortCutManager* Instance();
        KeyShortCut* GetPasteShortCut(size_t i) const;
        KeyShortCut* GetCopyShortCut(size_t i) const;
    protected:
        KeyShortCutManager();
    private:
        static KeyShortCutManager* m_instance;
        std::vector<KeyShortCut*> m_shortcuts;
        void LoadKeyShortCuts();
        std::vector<std::string> SelectFile();
        KeyShortCut* GetShortCutFromString(std::string shortcut, std::string event);
};

#endif