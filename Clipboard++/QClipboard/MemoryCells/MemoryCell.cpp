#include "MemoryCell.h"


MemoryCell::MemoryCell(std::string name, KeyShortCut* keyShortCutPaste, KeyShortCut* keyShortCutCopy) :
    m_text(""), 
    m_name(name),
    m_keyShortCutPaste(keyShortCutPaste),
    m_keyShortCutCopy(keyShortCutCopy)
{}

void MemoryCell::setText(const std::string& text) {
    m_text = text;
}

std::string MemoryCell::text() const {
    return m_text;
}

std::string MemoryCell::name() const {
    return m_name;
}

void MemoryCell::clear() {
    m_text = "";
}

KeyShortCut* MemoryCell::getKeyShortCutPaste() {
    return m_keyShortCutPaste;
}

KeyShortCut* MemoryCell::getKeyShortCutCopy() {
    return m_keyShortCutCopy;
}