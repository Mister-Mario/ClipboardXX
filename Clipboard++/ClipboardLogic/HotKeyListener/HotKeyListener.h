#ifndef HOTKEY_LISTENER_H
#define HOTKEY_LISTENER_H

#include <atomic>

extern std::atomic<bool> g_hotkeyPressed;

void HotkeyListenerThread();

#endif