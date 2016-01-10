#define _WIN32_WINNT 0x0601

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <conio.h>


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    AllocConsole();

    HANDLE outHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFOEX info;
    ZeroMemory(&info, sizeof(CONSOLE_SCREEN_BUFFER_INFOEX));
    info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    info.dwSize.X = 150;
    info.dwSize.Y = 80;
    info.dwCursorPosition.X = 10;
    info.dwCursorPosition.Y = 10;
    info.wAttributes = FOREGROUND_BLUE;
    info.srWindow.Left = 0;
    info.srWindow.Top = 0;
    info.srWindow.Right = 150;
    info.srWindow.Bottom = 80;
    info.dwMaximumWindowSize.X = 150;
    info.dwMaximumWindowSize.Y = 80;
    info.bFullscreenSupported = TRUE;
    info.ColorTable[0] = RGB(32, 32, 32);
    info.ColorTable[1] = RGB(255, 255, 255);

    SetConsoleScreenBufferInfoEx(outHandle, &info);

    //BOOL res = SetConsoleTextAttribute(outHandle, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    DWORD numWritten = 0;

    while(true)
    {
        if(_kbhit())
        {
            char ch = _getch();
            WriteFile(outHandle, "a", 1, &numWritten, NULL);
            COORD coord;
            coord.X = rand() % 150;
            coord.Y = rand() % 80;
            SetConsoleCursorPosition(outHandle, coord);
        }
    };
}