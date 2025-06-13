#include "PasteEvent.h"
#include <thread>
#include <chrono>
#include <iostream>

PasteEvent::PasteEvent(HWND lastWindow, MemoryCellManager* memoryCellManager) : m_memoryCellManager(memoryCellManager), WindowFocusEvent(lastWindow) {}

void PasteEvent::DoHandle(Rml::Event* event, Rml::StringList values) {
    auto clipboard = m_memoryCellManager->getMemoryCell(0);
    auto selectedCell = m_memoryCellManager->getMemoryCell(std::stoi(values[1]));
    if(!clipboard || !selectedCell)
        return;
    
    auto clipboardContents = clipboard->text();
    clipboard->setText(selectedCell->text());

    SimulatePaste();
}

bool PasteEvent::SimulatePaste()
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    INPUT inputs[4] = {};

    //Press Ctrl + V
    ip.ki.wVk = VK_LCONTROL;
    ip.ki.dwFlags = 0;
    inputs[0] = ip;

    ip.ki.wVk = 'V';
    ip.ki.dwFlags = 0;
    inputs[1] = ip;

    //Release keys as we are simulating the action
    ip.ki.wVk = 'V';
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    inputs[2] = ip;

    ip.ki.wVk = VK_LCONTROL;
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    inputs[3] = ip;

    UINT eventos_enviados = SendInput(4, inputs, sizeof(INPUT));

    return eventos_enviados == 4;
}
