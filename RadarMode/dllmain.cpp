#include "pch.h"
#include <thread>

int mode = 0;

void AddMessageJumpQ(const char* text, unsigned int time, unsigned short flag, bool bPreviousBrief)
{
    ((void(__cdecl*)(const char*, unsigned int, unsigned short, bool))0x69F1E0)(text, time, flag, bPreviousBrief);
}

struct stDLLProject
{
    LONG PrevWndFunc;
} pDLLProject;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_KEYUP:
    {
        switch (wParam)
        {
        case VK_F10:
        {
            break; // костыли и велосипеды но без него донт ворк
        }
        case VK_F11:
        {
            if (mode == 0) {
                AddMessageJumpQ("Mode = 1", 500, NULL, false);
                mode = 1;
                memset(reinterpret_cast <void*>(0xBA676C), mode, 1);
            }
            else if (mode == 1) {
                AddMessageJumpQ("Mode = 2", 500, NULL, false);
                mode = 2;
                memset(reinterpret_cast <void*>(0xBA676C), mode, 1);
            }
            else if (mode == 2) {
                AddMessageJumpQ("Mode = 0", 500, NULL, false);
                mode = 0;
                memset(reinterpret_cast <void*>(0xBA676C), mode, 1);
            }
        }
        }
    }
    }
    return CallWindowProcA(WNDPROC(pDLLProject.PrevWndFunc), hwnd, uMsg, wParam, lParam);
}


void InitializeAndLoad() {
    while (*reinterpret_cast<unsigned char*>(0xC8D4C0) != 9) {
        std::this_thread::sleep_for(std::chrono::milliseconds(266u));
    }
    pDLLProject.PrevWndFunc = SetWindowLongA(FindWindowA(NULL, "GTA: San Andreas"), GWL_WNDPROC, LONG(WindowProc));
    AddMessageJumpQ("~r~~h~[RadarMode] ~w~Author: ~g~~h~~h~~h~FooOoott. ~w~Use ~g~~h~~h~~h~F11", 5000, 0, false);
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        std::thread(InitializeAndLoad).detach();
        break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}