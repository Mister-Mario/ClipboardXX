#include "PasteEvent.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <Clipboard/ClipboardListener.h>

/**
 * @brief Constructor for the PasteEvent.
 * @param memoryCellManager A pointer to the manager for clipboard memory cells.
 */
PasteEvent::PasteEvent(MemoryCellManager* memoryCellManager) : m_memoryCellManager(memoryCellManager) {}

/**
 * @brief Performs the core logic of the paste event.
 * @details This method is called by the base WindowFocusEvent::handle method after focus has been set.
 * It sets the content of the selected cell to the system clipboard and then simulates a paste (Ctrl+V) command.
 * An empty callback is temporarily added to ClipboardListener to prevent the application from re-capturing its own paste action.
 * @param event The RmlUi event that triggered this action.
 * @param values A list of string parameters, where values[1] is expected to be the index of the selected memory cell.
 */
void PasteEvent::DoHandle(Rml::Event* event, Rml::StringList values) {
    auto clipboard = m_memoryCellManager->getMemoryCell(0);
    auto selectedCell = m_memoryCellManager->getMemoryCell(std::stoi(values[1]));
    if(!clipboard || !selectedCell)
        return;

    auto clipboardContents = clipboard->text();
    clipboard->setText(selectedCell->text());

    ClipboardListener::Instance()->AddCallback([](const std::string text) {}); //Empty callback to not launch the base action

    SimulatePaste();
}

/**
 * @brief Simulates a paste (Ctrl+V) keyboard shortcut.
 * @details Uses the Windows SendInput API to programmatically press and release the Left Control and 'V' keys,
 * which triggers a paste action in the currently focused application.
 * @return bool True if the input events were sent successfully, false otherwise.
 */
bool PasteEvent::SimulatePaste()
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    INPUT inputs[4] = {};

    // Press Ctrl + V
    ip.ki.wVk = VK_LCONTROL;
    ip.ki.dwFlags = 0;
    inputs[0] = ip;

    ip.ki.wVk = 'V';
    ip.ki.dwFlags = 0;
    inputs[1] = ip;

    // Release keys as we are simulating the action
    ip.ki.wVk = 'V';
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    inputs[2] = ip;

    ip.ki.wVk = VK_LCONTROL;
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    inputs[3] = ip;

    UINT eventos_enviados = SendInput(4, inputs, sizeof(INPUT));

    return eventos_enviados == 4;
}
