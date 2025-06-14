#ifndef GLOBAL_FUNCTION_H
#define GLOBAL_FUNCTION_H

#include <RmlUi/Core.h>
#include <atomic>

#ifdef _WIN32
#include <windows.h>
#endif

namespace GlobalFunctions {

    extern Rml::Context* context;
    extern bool isWindowOpened;
    extern bool isShortCutsOpened;
    extern bool running;
    extern std::atomic<bool> g_hotkeyPressed;

#ifdef _WIN32
    extern HWND lastWindow;
#endif


    void captureHWND();
    void hideAllDocuments();
    void showShortcuts(Rml::ElementDocument* shortcuts_doc);
    void quit();

}

#endif 