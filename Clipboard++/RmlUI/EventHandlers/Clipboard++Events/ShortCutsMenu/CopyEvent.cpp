#include "CopyEvent.h"
#include <thread>
#include <chrono>
#include <iostream>
#include "QClipboard/Clipboard/ClipboardListener.h"

/**
 * @brief Constructor for the CopyEvent.
 * @param memoryCellManager A pointer to the manager for clipboard memory cells.
 */
CopyEvent::CopyEvent(MemoryCellManager* memoryCellManager) : m_memoryCellManager(memoryCellManager) {}

/**
 * @brief Performs the core logic of the copy event.
 * @details This method is called by the base WindowFocusEvent::handle method after focus has been set.
 * It sets up a one-time callback on the ClipboardListener. This callback will capture the text from the
 * next copy operation and save it directly into the specified memory cell. It then simulates a copy (Ctrl+C) command.
 * @param event The RmlUi event that triggered this action.
 * @param values A list of string parameters, where values[1] is expected to be the index of the target memory cell.
 */
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

/**
 * @brief Simulates a copy (Ctrl+C) keyboard shortcut.
 * @details Uses the Windows SendInput API to programmatically press and release the Left Control and 'C' keys,
 * which triggers a copy action in the currently focused application.
 * @return bool True if the input events were sent successfully, false otherwise.
 */
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
