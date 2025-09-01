#include "ClipboardListener.h"
#include <iostream>

/**
 * @brief Provides access to the singleton instance of the ClipboardListener.
 * @return ClipboardListener* A pointer to the singleton instance.
 */
ClipboardListener* ClipboardListener::Instance() {
    static ClipboardListener instance;
    return &instance;
}

/**
 * @brief Constructor for the ClipboardListener.
 */
ClipboardListener::ClipboardListener() {}

/**
 * @brief Initializes the listener with a specific QClipboard object.
 * @details Stores a pointer to the Qt clipboard and connects its `dataChanged` signal
 * to the `OnSystemClipboardChanged` slot, which allows this class to react to
 * system-wide clipboard changes.
 * @param clipboard A pointer to the QApplication's clipboard object.
 */
void ClipboardListener::Initialize(QClipboard* clipboard) {
    m_clipboard = clipboard;
    connect(m_clipboard, &QClipboard::dataChanged, this, &ClipboardListener::OnSystemClipboardChanged); 
}

/**
 * @brief Slot that is triggered when the system clipboard content changes.
 * @details It checks if there is a one-time action in the queue. If so, it executes
 * that action and removes it. If the queue is empty, it executes the permanent base action, if one exists.
 * This logic allows for temporarily overriding the default clipboard handling.
 */
void ClipboardListener::OnSystemClipboardChanged()
{
    if (!m_clipboard) return;

    const std::string new_text = m_clipboard->text().toStdString();

    if (m_actionQueue.empty()) {
        // If no one-time actions are queued, execute the default base action.
        if(m_baseAction)
            m_baseAction(new_text);
    }
    else {
        // Execute and pop the next one-time action from the queue.
        std::function<void(const std::string&)> action_to_execute = m_actionQueue.front();
        m_actionQueue.pop();

        if (action_to_execute) {
            action_to_execute(new_text);
        }
    }
}

/**
 * @brief Adds a one-time callback to be executed on the next clipboard change.
 * @details The provided callback will be executed only once, for the very next
 * `dataChanged` signal, and will then be discarded.
 * @param callback The function to execute.
 */
void ClipboardListener::AddCallback(const std::function<void(const std::string&)>& callback)
{
    m_actionQueue.push(callback);
}

/**
 * @brief Sets a permanent callback to be executed on every clipboard change.
 * @details This callback serves as the default action whenever the action queue is empty.
 * Any previously set base callback will be overwritten.
 * @param callback The function to execute as the default action.
 */
void ClipboardListener::AddBaseCallback(const std::function<void(const std::string&)>& callback){
    m_baseAction = callback;
}
