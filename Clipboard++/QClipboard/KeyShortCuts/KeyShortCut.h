#ifndef KEY_SHORT_CUT_H
#define KEY_SHORT_CUT_H

#include <vector>
#include <string>
#include <RmlUi/Core/Input.h>

class KeyShortCut {
    public:
        KeyShortCut(std::string event, std::vector<Rml::Input::KeyIdentifier> shortCutCombination);
        std::vector<Rml::Input::KeyIdentifier> getShortCut() const;
        void setShortCut(const std::vector<Rml::Input::KeyIdentifier>& newCombination);
        std::string getEvent() const;
    private:
        std::vector<Rml::Input::KeyIdentifier> m_shortCutCombination;
        std::string m_event;
};

#endif