#ifndef WINDOW_FOCUS_EVENT_H
#define WINDOW_FOCUS_EVENT_H

#include "Clipboard++Event.h"

#ifdef _WIN32
#include <windows.h>
#endif


class WindowFocusEvent : public ClipboardEvent {
public:
    explicit WindowFocusEvent();
    virtual ~WindowFocusEvent() = default;
    void handle(Rml::Event* event, Rml::StringList values) final;

protected:

    virtual void Attach();
    virtual void ShowWindow();
    virtual void DoHandle(Rml::Event* event, Rml::StringList values) = 0;
    virtual void DeAttach();

private:
    #ifdef _WIN32
    DWORD m_currentThreadId = 0;
    DWORD m_targetThreadId = 0;
    #endif
};

#endif