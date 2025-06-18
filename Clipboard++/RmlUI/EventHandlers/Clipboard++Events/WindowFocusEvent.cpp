#include "WindowFocusEvent.h"
#include <iostream>
#include <thread>
#include <chrono>

extern HWND lastWindowClipboardXX;

/**
 * @brief Constructor for WindowFocusEvent.
 */
WindowFocusEvent::WindowFocusEvent() {}

/**
 * @brief Handles the main logic for switching window focus.
 * @details This function orchestrates attaching to the target window's input thread,
 * making the window visible and foreground, executing the specific derived event logic,
 * and then detaching from the input thread.
 * @param event The RmlUi event that triggered this action.
 * @param values A list of string parameters associated with the event.
 */
void WindowFocusEvent::handle(Rml::Event* event, Rml::StringList values) {
    if (!IsWindow(lastWindowClipboardXX)) return;

    Attach();
    ShowWindow();

    // A short delay to allow the OS to process window focus changes.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    DoHandle(event, values);
    
    DeAttach();
}

/**
 * @brief Attaches the current thread's input processing to the target window's thread.
 * @details This is a Windows-specific mechanism required to reliably send input
 * (like keystrokes) to another application's window.
 */
void WindowFocusEvent::Attach() {
#ifdef _WIN32
    m_currentThreadId = GetCurrentThreadId();
    m_targetThreadId = GetWindowThreadProcessId(lastWindowClipboardXX, NULL);

    if (m_targetThreadId != 0)
        AttachThreadInput(m_currentThreadId, m_targetThreadId, TRUE);
#endif
}

/**
 * @brief Ensures the target window is visible and brings it to the foreground.
 * @details If the window is minimized (iconic), it will be restored. It then
 * sets the window as the foreground window, giving it user focus.
 */
void WindowFocusEvent::ShowWindow() {
#ifdef _WIN32
    if (IsIconic(lastWindowClipboardXX)) {
        ::ShowWindow(lastWindowClipboardXX, SW_RESTORE);
    }

    SetForegroundWindow(lastWindowClipboardXX);
#endif
}

/**
 * @brief Detaches the current thread's input from the target window's thread.
 * @details This reverses the action of Attach(), cleaning up the input state
 * and preventing unintended side effects.
 */
void WindowFocusEvent::DeAttach() {
#ifdef _WIN32
    if (m_targetThreadId != 0) {
        AttachThreadInput(m_currentThreadId, m_targetThreadId, FALSE);
    }
#endif
}
