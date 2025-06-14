#ifndef EDIT_VIEW_MODEL_H
#define EDIT_VIEW_MODEL_H

#include <KeyShortCuts/KeyShortCut.h>
#include <RmlUi/Core/Input.h>
#include <vector>

class EditViewModel {
    public:
        static EditViewModel* Instance();
        void RegisterKey(Rml::Input::KeyIdentifier key);
        void ResetNewShortCut();
        std::vector<Rml::Input::KeyIdentifier> GetNewShortCut() const; 
        void SetSelectedShortCut(KeyShortCut* selectedShortCut);
        KeyShortCut* GetSelectedShortCut();
    protected:
        EditViewModel();
        ~EditViewModel();
    private:
        std::vector<Rml::Input::KeyIdentifier> newShortCut;
        KeyShortCut* m_selectedShortCut;
};

#endif