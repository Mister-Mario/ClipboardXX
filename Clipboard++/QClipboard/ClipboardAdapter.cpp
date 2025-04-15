#include "ClipboardAdapter.h"

ClipboardAdapter::ClipboardAdapter(QClipboard* clipboard) : m_clipboard(clipboard) {
    // Empty constructor
}

void ClipboardAdapter::setText(const std::string text) {
    m_clipboard->setText(QString::fromStdString(text));
}

std::string ClipboardAdapter::text() const {
    return m_clipboard->text().toStdString();
}

void ClipboardAdapter::clear() const {
    m_clipboard->clear();
}