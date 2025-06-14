#include "GlobalFunctions.h"
#include "RmlUi_Backend.h"

namespace GlobalFunctions {

    Rml::Context* context = nullptr;
    bool isWindowOpened = false;
    bool running = true;
    std::atomic<bool> g_hotkeyPressed{false};

#ifdef _WIN32
    HWND lastWindow = NULL;
#endif


    void captureHWND() {
    #ifdef _WIN32
        if (!Backend::IsWindowShown()) {
            lastWindow = GetForegroundWindow();
        }
    #endif
    }

    void hideAllDocuments() {
        if (!context) return;
        for (int i = context->GetNumDocuments() - 1; i >= 0; --i) {
            if(auto doc = context->GetDocument(i)) {
                doc->Hide();
            }
        }
    }

    void showShortcuts(Rml::ElementDocument* shortcuts_doc) {
        if (!context || !shortcuts_doc) return;

        hideAllDocuments();
        shortcuts_doc->Show();

        Backend::ModifyWindowSize(context, 900/16.0f, 350/16.0f);
        Backend::SetBorder(false);
        Backend::ShowWindow();
        
        isWindowOpened = true;
    }

    void quit() {
        running = false;
    }
}