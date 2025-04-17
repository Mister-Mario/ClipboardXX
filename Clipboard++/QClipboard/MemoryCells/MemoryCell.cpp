#include "MemoryCell.h"

MemoryCell::MemoryCell() : m_text("") {
    // Initialize an empty memory cell
}

void MemoryCell::setText(const std::string& text) {
    m_text = text;
}

std::string MemoryCell::text() const {
    return m_text;
}

void MemoryCell::clear() {
    m_text = "";
}