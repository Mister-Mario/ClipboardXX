#include <EditViewModel.h>

EditViewModel* EditViewModel::Instance() {
    static EditViewModel instance;
    return &instance;
}

EditViewModel::EditViewModel() {}

EditViewModel::~EditViewModel() {}

void EditViewModel::RegisterKey(Rml::Input::KeyIdentifier key) {
    newShortCut.push_back(key);
}
void EditViewModel::ResetNewShortCut() {
    newShortCut.clear();
}
std::vector<Rml::Input::KeyIdentifier> EditViewModel::GetNewShortCut() const{
    return newShortCut;
}

void EditViewModel::SetSelectedShortCut(KeyShortCut* selectedShortCut) {
    m_selectedShortCut = selectedShortCut;
}

KeyShortCut* EditViewModel::GetSelectedShortCut() {
    return m_selectedShortCut;
}