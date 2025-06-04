#include "KeyShortCut.h"
#include "Utils/FileManager.h"

constexpr int HOTKEY_ID_BASE = 0x7000;

KeyShortCut::KeyShortCut(int id_offset, UINT fsModifiers, UINT vk)
    : m_id(HOTKEY_ID_BASE + id_offset),
      m_fsModifiers(fsModifiers),
      m_vk(vk)
{}

KeyShortCut::~KeyShortCut() {
    unregisterKeyShortCut();
}

bool KeyShortCut::registerKeyShortCut() {
    //0x4000 is the NOREPEAT FLAG
    return RegisterHotKey(NULL, m_id, m_fsModifiers | 0x4000, m_vk);
}

bool KeyShortCut::unregisterKeyShortCut() {
   return UnregisterHotKey(NULL, m_id);
}