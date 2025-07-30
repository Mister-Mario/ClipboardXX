#include "ClipboardXX.h"

#if defined RMLUI_PLATFORM_WIN32
#include <RmlUi_Include_Windows.h>

#ifdef _WIN32
#include <windows.h>
HANDLE g_singleInstanceMutex = NULL;

/**
 * @brief Checks if another instance of the application is already running.
 * @return true if this is the only instance, false if another is already running.
 */
bool IsFirstInstance()
{
    const char* mutexName = "ClipboardXX-Mutex-C5B4A1B2-E1A7-44E2-A5A4-2B4E4D8C7B9F";
    g_singleInstanceMutex = CreateMutexA(NULL, TRUE, mutexName);

    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        if (g_singleInstanceMutex) {
            CloseHandle(g_singleInstanceMutex);
            g_singleInstanceMutex = NULL;
        }
        return false;
    }
    return true;
}

/**
 * @brief Releases the Mutex when the application closes.
 */
void ReleaseMutexHandle()
{
    if (g_singleInstanceMutex)
    {
        ReleaseMutex(g_singleInstanceMutex);
        CloseHandle(g_singleInstanceMutex);
    }
}
#endif

int APIENTRY WinMain(HINSTANCE, HINSTANCE, char* command_line, int)
{
#ifdef _WIN32
    if (!IsFirstInstance())
    {
        return 0;
    }
#endif

    ClipboardXX app(__argc, __argv);
    int result = app.Run();

#ifdef _WIN32
    ReleaseMutexHandle();
#endif

    return result;
}
#else
int main(int argc, char** argv)
{
    return ClipboardXX(argc, argv).Run();
}
#endif