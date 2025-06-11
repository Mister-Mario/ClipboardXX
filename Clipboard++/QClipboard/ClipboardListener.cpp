#include "ClipboardListener.h"
#include <iostream>

ClipboardListener* ClipboardListener::Instance() {
    static ClipboardListener instance;
    return &instance;
}

ClipboardListener::ClipboardListener() {}

void ClipboardListener::Initialize(QClipboard* clipboard) {
    m_clipboard = clipboard;
    connect(m_clipboard, &QClipboard::dataChanged, this, &ClipboardListener::OnSystemClipboardChanged);
}

void ClipboardListener::OnSystemClipboardChanged()
{
    if (!m_clipboard) return;

    const std::string new_text = m_clipboard->text().toStdString();

    if (m_actionQueue.empty()) {
        std::cout << "Cambio en el portapapeles detectado, pero no hay acciones en la cola." << std::endl;
        return;
    }
    else {
        std::function<void(const std::string&)> action_to_execute = m_actionQueue.front();

        m_actionQueue.pop();

        if (action_to_execute) {
            action_to_execute(new_text);
        }
    }
}

void ClipboardListener::AddCallback(const std::function<void(const std::string&)>& callback)
{
    m_actionQueue.push(callback);
}