#include "ClipboardXX.h"

#if defined RMLUI_PLATFORM_WIN32
#include <RmlUi_Include_Windows.h>
int APIENTRY WinMain(HINSTANCE, HINSTANCE, char* command_line, int)
{
    return ClipboardXX(__argc, __argv).Run();
}
#else
int main(int argc, char** argv)
{
    return ClipboardXX(argc, argv).Run();
}
#endif