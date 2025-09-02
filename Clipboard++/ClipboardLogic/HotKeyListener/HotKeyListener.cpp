#include "HotKeyListener.h"
#include <iostream>


#ifdef _WIN32
#include <windows.h>

// Global atomic flag to indicate when the hotkey has been pressed.
std::atomic<bool> g_hotkeyPressed{false};

/**
 * @brief The main function for the hotkey listener thread (Windows implementation).
 * @details This function runs in a dedicated thread and sets up a system-wide hotkey
 * (Win + Alt + V). It enters a message loop, waiting for the hotkey press. When the
 * hotkey is detected, it sets a global atomic flag to true.
 * @note This is a blocking function and is intended to be run in its own thread.
 */
void HotkeyListenerThread() {
    const int MY_HOTKEY_ID = 1;

    // Register a system-wide hotkey: Win + Alt + V.
    // 0x4000 is MOD_NOREPEAT to prevent the message from being sent repeatedly when the key is held down.
    if (!RegisterHotKey(NULL, MY_HOTKEY_ID, MOD_WIN | MOD_ALT | 0x4000, 'V')) {
        return;
    }

    // Standard Windows message loop to listen for hotkey events.
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0) != 0) {
        if (msg.message == WM_HOTKEY) {
            if (msg.wParam == MY_HOTKEY_ID) {
                g_hotkeyPressed.store(true);
            }
        }
    }

    // Clean up the hotkey when the thread exits.
    UnregisterHotKey(NULL, MY_HOTKEY_ID);
}

#else

// Global atomic flag (stub for non-Windows platforms).
std::atomic<bool> g_hotkeyPressed{false};

/**
 * @brief The main function for the hotkey listener thread (non-Windows stub).
 * @details This is a placeholder for non-Windows operating systems where the
 * RegisterHotKey API is not available. It does nothing.
 */
void HotkeyListenerThread() {
    // Nothing to do for Linux in this implementation.
}

#endif
