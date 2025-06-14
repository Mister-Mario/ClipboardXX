#include "HotKeyListener.h"
#include <iostream>


#ifdef _WIN32
#include <windows.h>

std::atomic<bool> g_hotkeyPressed{false};

void HotkeyListenerThread() {
    const int MY_HOTKEY_ID = 1;

    if (!RegisterHotKey(NULL, MY_HOTKEY_ID, MOD_WIN | MOD_ALT | 0x4000, 'V')) {
        return;
    }

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0) != 0) {
        if (msg.message == WM_HOTKEY) {
            if (msg.wParam == MY_HOTKEY_ID) {
                g_hotkeyPressed.store(true);
            }
        }
    }

    UnregisterHotKey(NULL, MY_HOTKEY_ID);
}

#else


std::atomic<bool> g_hotkeyPressed{false};
void HotkeyListenerThread() {
    // Nothing to do for Linux, macOS, etc.
}

#endif