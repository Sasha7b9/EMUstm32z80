#include "stdafx.h"


#include "Console.h"


extern "C"
{
    #include "DLLmain.h"
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern OutStruct params;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Console::Console()
{
    AllocConsole();

    outHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFOEX info;
    ZeroMemory(&info, sizeof(CONSOLE_SCREEN_BUFFER_INFOEX));
    info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    info.dwSize.X = WIDTH;
    info.dwSize.Y = HEIGHT;
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

    prevUpdate = GetTickCount();
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
bool Console::Update()
{
    if(GetTickCount() - prevUpdate > 40)
    {
        WriteRegisters();
        prevUpdate = GetTickCount();
    }

    if(_kbhit())
    {
        int ch = _getch();
        if(ch == 27)
        {
            return false;
        }
        if(ch == 0x08)
        {
            AddToCommandLine(0x08);
            AddToCommandLine(' ');
        }
        if(ch == 0xe0 || ch == 0x0)
        {
            _getch();
            return true;
        }
        
        AddToCommandLine((char)ch);
    }
    return true;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Console::AddToCommandLine(char symbol)
{
    char buffer[1];
    buffer[0] = symbol;

    WriteFile(outHandle, buffer, 1, NULL, NULL);

    posCommandLine = posCommandLine + (symbol == 0x08 ? -1 : 1);

    if(posCommandLine < 0)
    {
        posCommandLine = 0;
    }
}


#define WRITE8(x, y, name, value)   \
    WriteString(x, y, name);        \
    WriteString(x + 1, y, "=");     \
    Write8bit(x + 2, y, value);

#define WRITE16(x, y, name, value)  \
    WriteString(x, y, name);        \
    WriteString(x + 2, y, "=");     \
    Write16bit(x + 3, y, value);


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Console::WriteRegisters()
{
    REGS *regs = params.regs;

    for(int i = 0; i < WIDTH; i++)
    {
        WriteString(i, HEIGHT - 2, "-");
        WriteString(i, HEIGHT - 5, "-");
    }

    WriteString(35, HEIGHT - 3, "|");
    WriteString(35, HEIGHT - 4, "|");

    WriteString(53, HEIGHT - 3, "|");
    WriteString(53, HEIGHT - 4, "|");

    int dY = HEIGHT - 4;

    WRITE8(0, dY, "A", regs->r8[ADDR_A]);

    WRITE8(5, dY, "B", regs->r8[ADDR_B]);

    WRITE8(10, dY, "C", regs->r8[ADDR_C]);

    WRITE16(5, 1 + dY, "BC", regs->r16[ADDR_BC]);

    WRITE8(15, dY, "D", regs->r8[ADDR_D]);

    WRITE8(20, dY, "E", regs->r8[ADDR_E]);

    WRITE16(15, 1 + dY, "DE", regs->r16[ADDR_DE]);

    WRITE8(25, dY, "H", regs->r8[ADDR_H]);

    WRITE8(30, dY, "L", regs->r8[ADDR_L]);

    WRITE16(25, 1 + dY, "HL", regs->r16[ADDR_HL]);

    WRITE16(37, dY, "IX", regs->r16[ADDR_IX]);

    WRITE16(37, 1 + dY, "IY", regs->r16[ADDR_IY]);

    WRITE16(45, dY, "SP", regs->r16[ADDR_SP]);

    WRITE16(45, 1 + dY, "PC", regs->r16[ADDR_PC]);

    WriteFlags(55, dY);
}


#define WRITE_FLAG(x, y, name, bit) \
    WriteString(x, y, name);        \
    Write4bit(x, y + 1, (uint8)((flags >> bit) & 1));


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Console::WriteFlags(int x, int y)
{
    uint8 flags = params.regs->r8[ADDR_F];

    WRITE_FLAG(x, y, "S", 7);

    WRITE_FLAG(x + 2, y, "Z", 6);

    WRITE_FLAG(x + 4, y, "H", 4);

    WRITE_FLAG(x + 6, y, "PV", 2);

    WRITE_FLAG(x + 9, y, "N", 1);

    WRITE_FLAG(x + 11, y, "C", 0);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Console::WriteString(int x, int y, char *str)
{
    COORD coord;
    coord.X = (SHORT)x;
    coord.Y = (SHORT)y;

    SetConsoleCursorPosition(outHandle, coord);
    //WriteFile(outHandle, str, strlen(str), NULL, NULL);
    WriteConsoleA(outHandle, str, strlen(str), NULL, NULL);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Console::Write4bit(int x, int y, uint8 byte)
{
    char buffer[3];
    sprintf_s(buffer, 3, "%01X", byte);
    WriteString(x, y, buffer);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Console::Write8bit(int x, int y, uint8 byte)
{
    char buffer[3];
    sprintf_s(buffer, 3, "%02X", byte);
    WriteString(x, y, buffer);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Console::Write16bit(int x, int y, uint16 word)
{
    char buffer[5];
    sprintf_s(buffer, 5, "%04X", word);
    WriteString(x, y, buffer);
}
