#include "ClipboardAdapter.h"


ClipboardAdapter::ClipboardAdapter(QClipboard* clipboard, KeyShortCut* keyShortCutPaste, KeyShortCut* keyShortCutCopy) :
    m_clipboard(clipboard),
    m_keyShortCutPaste(keyShortCutPaste),
    m_keyShortCutCopy(keyShortCutCopy)
{}

void ClipboardAdapter::setText(const std::string& text) {
    m_clipboard->setText(QString::fromStdString(text));
}

std::string ClipboardAdapter::text() const {
    return m_clipboard->text().toStdString();
}

std::string ClipboardAdapter::name() const {
    return "clipboard";
}

void ClipboardAdapter::clear() {
    m_clipboard->clear();
}

KeyShortCut* ClipboardAdapter::getKeyShortCutPaste() {
    return m_keyShortCutPaste;
}

KeyShortCut* ClipboardAdapter::getKeyShortCutCopy() {
    return m_keyShortCutCopy;
}