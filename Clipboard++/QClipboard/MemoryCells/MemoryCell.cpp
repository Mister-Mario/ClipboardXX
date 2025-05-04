#include "MemoryCell.h"

MemoryCell::MemoryCell(std::string name) : m_text(""), m_name(name) {
    // Initialize an empty memory cell
}

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