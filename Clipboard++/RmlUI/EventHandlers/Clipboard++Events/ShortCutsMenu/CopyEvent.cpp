#include "CopyEvent.h"
#include <thread>
#include <chrono>
#include <iostream>
#include "QClipboard/ClipboardListener.h"

CopyEvent::CopyEvent(HWND lastWindow, MemoryCellManager* memoryCellManager) : m_memoryCellManager(memoryCellManager), WindowFocusEvent(lastWindow) {}

void CopyEvent::DoHandle(Rml::Event* event, Rml::StringList values) {
    auto clipboard = m_memoryCellManager->getMemoryCell(0);
    size_t cellIndex = std::stoi(values[1]);
    auto selectedCell = m_memoryCellManager->getMemoryCell(cellIndex);
    if(!clipboard || !selectedCell)
        return;

    ClipboardListener::Instance()->AddCallback([this, cellIndex](const std::string text) {
        auto freshSelectedCell = m_memoryCellManager->getMemoryCell(cellIndex);
        if (freshSelectedCell)
            freshSelectedCell->setText(text);
    });
    
    SimulateCopy();
}

bool CopyEvent::SimulateCopy()
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    INPUT inputs[4] = {};

    //Press Ctrl + C
    ip.ki.wVk = VK_LCONTROL;
    ip.ki.dwFlags = 0;
    inputs[0] = ip;

    ip.ki.wVk = 'C';
    ip.ki.dwFlags = 0;
    inputs[1] = ip;

    //Release keys as we are simulating the action
    ip.ki.wVk = 'C';
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    inputs[2] = ip;

    ip.ki.wVk = VK_LCONTROL;
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    inputs[3] = ip;

    UINT eventos_enviados = SendInput(4, inputs, sizeof(INPUT));

    return eventos_enviados != 4;
}