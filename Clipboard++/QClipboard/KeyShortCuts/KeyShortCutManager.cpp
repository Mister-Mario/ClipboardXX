#include <KeyShortCutManager.h>

KeyShortCutManager* KeyShortCutManager::m_instance = nullptr;

KeyShortCutManager::KeyShortCutManager(){}

KeyShortCutManager* KeyShortCutManager::Instance() {
    if(m_instance == nullptr) {
        m_instance = new KeyShortCutManager();
    }
    return m_instance;
}