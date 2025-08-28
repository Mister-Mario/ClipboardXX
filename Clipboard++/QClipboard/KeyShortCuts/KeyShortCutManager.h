#ifndef KEY_SHORT_CUT_MANAGER_H
#define KEY_SHORT_CUT_MANAGER_H

#include "KeyShortCut.h"
#include <MemoryCells/MemoryCellManager.h>
#include "../Utils/IFileManager.h"

class KeyShortCutManager {
    public:
        static KeyShortCutManager* Instance();
        KeyShortCut* GetPasteShortCut(size_t i) const;
        KeyShortCut* GetCopyShortCut(size_t i) const;
        KeyShortCut* FilterShortCuts(Rml::Input::KeyIdentifier key);
        void ModifyKeyShortCuts(MemoryCellManager* memoryCellManager);
        void Initialize(IFileManager* fileManager);
    protected:
        KeyShortCutManager();
    private:
        static KeyShortCutManager* m_instance;
        std::vector<KeyShortCut*> m_shortcutsBase;
        std::vector<KeyShortCut*> m_shortcuts;
        IFileManager* m_fileManager;
        int keysFiltered = 0;
        Rml::Input::KeyIdentifier lastKeyPressed = Rml::Input::KI_UNKNOWN;
        void LoadKeyShortCuts();
        std::vector<std::string> SelectFile();
        KeyShortCut* GetShortCutFromString(std::string shortcut, std::string event);
        std::vector<KeyShortCut*> GetBaseList() const;
        void WriteShortCuts();
};

#endif