#include "WindowFocusEvent.h"
#include <iostream>
#include <thread>
#include <chrono>

WindowFocusEvent::WindowFocusEvent(HWND lastWindow) : m_lastWindow(lastWindow) {}


void WindowFocusEvent::handle(Rml::Event* event, Rml::StringList values) {
    if (!IsWindow(m_lastWindow)) return;

    Attach();
    ShowWindow();

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    DoHandle(event, values);
    
    DeAttach();
}


void WindowFocusEvent::Attach() {
#ifdef _WIN32

    m_currentThreadId = GetCurrentThreadId();
    m_targetThreadId = GetWindowThreadProcessId(m_lastWindow, NULL);

    if (m_targetThreadId != 0)
        AttachThreadInput(m_currentThreadId, m_targetThreadId, TRUE);
#endif
}

void WindowFocusEvent::ShowWindow() {
#ifdef _WIN32

    if (IsIconic(m_lastWindow)) {
        ::ShowWindow(m_lastWindow, SW_RESTORE);
    }

    SetForegroundWindow(m_lastWindow);
#endif
}

void WindowFocusEvent::DeAttach() {
#ifdef _WIN32
    if (m_targetThreadId != 0) {
        AttachThreadInput(m_currentThreadId, m_targetThreadId, FALSE);
    }
#endif
}