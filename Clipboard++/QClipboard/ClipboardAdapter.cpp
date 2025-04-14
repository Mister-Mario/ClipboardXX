#include "ClipboardAdapter.h"

ClipboardAdapter::ClipboardAdapter(QClipboard* clipboard) : m_clipboard(clipboard) {
    // Empty constructor
}

void ClipboardAdapter::setText(const QString& text) {
    m_clipboard->setText(text);
}

QString ClipboardAdapter::text() const {
    return m_clipboard->text();
}

void ClipboardAdapter::clear() const {
    m_clipboard->clear();
}