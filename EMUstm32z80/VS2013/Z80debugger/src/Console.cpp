#include "stdafx.h"


#include "Console.h"
#include "DataBase.h"


extern "C"
{
    #include "DLLmain.h"
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern OutStruct params;

extern DataBase base;


using std::vector;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Console::Console()
{
    AllocConsole();

    outHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFOEX info;
    info.cbSize = sizeof(info);

    GetConsoleScreenBufferInfoEx(outHandle, &info);

    info.dwSize.X = WIDTH_CONSOLE;
    info.dwSize.Y = HEIGHT_CONSOLE;
    info.dwCursorPosition.X = 10;
    info.dwCursorPosition.Y = 10;
    info.srWindow.Left = 0;
    info.srWindow.Top = 0;
    info.srWindow.Right = 150;
    info.srWindow.Bottom = 80;
    info.dwMaximumWindowSize.X = 150;
    info.dwMaximumWindowSize.Y = 80;

    SetConsoleScreenBufferInfoEx(outHandle, &info);

    prevUpdate = GetTickCount();

    COORD coord;
    coord.X = (SHORT)posCommandLine;
    coord.Y = HEIGHT_CONSOLE - 1;
    SetConsoleCursorPosition(outHandle, coord);

    for(int i = 0; i < WIDTH_CONSOLE * HEIGHT_CONSOLE; i++)
    {
        backBuffer[i].Char.AsciiChar = ' ';
        backBuffer[i].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
    }

    CONSOLE_CURSOR_INFO cursorInfo = {1, 0};
    SetConsoleCursorInfo(outHandle, &cursorInfo);

    ClearCommandLine();
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
bool Console::Update()
{
    if(GetTickCount() - prevUpdate > 40)
    {
        ClearBackBuffer();

        WriteScreen();

        prevUpdate = GetTickCount();

        WriteBackBuffer();
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
        if(ch == 13)
        {
            RunCommand();
            return true;
        }
        
        AddToCommandLine((char)ch);
    }
    return true;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Console::AddToCommandLine(char symbol)
{
    if(symbol == 0x08)
    {
        commandLine[posCommandLine] = ' ';
        if(posCommandLine > 0)
        {
            posCommandLine--;
        }
        commandLine[posCommandLine] = '_';
    }
    else if(isascii(symbol))
    {
        commandLine[posCommandLine++] = symbol;
        commandLine[posCommandLine] = '_';
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
void Console::WriteScreen()
{
    static char limiter[1024];
    static bool first = true;
    if(first)
    {
        for(int i = 0; i < WIDTH_CONSOLE; i++)
        {
            limiter[i] = '-';
        }
        limiter[WIDTH_CONSOLE + 1] = 0;
        first = false;
    }

    WriteString(0, HEIGHT_CONSOLE - 2, limiter);
    WriteString(0, HEIGHT_CONSOLE - 5, limiter);

    int dY = HEIGHT_CONSOLE - 4;

    WriteRegisters(dY);

    WriteFlags(55, dY);

    WriteListing();
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Console::WriteRegisters(int dY)
{
    REGS *regs = params.regs;

    WriteString(35, HEIGHT_CONSOLE - 3, "|");
    WriteString(35, HEIGHT_CONSOLE - 4, "|");

    WriteString(53, HEIGHT_CONSOLE - 3, "|");
    WriteString(53, HEIGHT_CONSOLE - 4, "|");

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

    WRITE_FLAG(x + 4, y, ".", 5);

    WRITE_FLAG(x + 6, y, "H", 4);

    WRITE_FLAG(x + 8, y, ".", 3);

    WRITE_FLAG(x + 10, y, "PV", 2);

    WRITE_FLAG(x + 13, y, "N", 1);

    WRITE_FLAG(x + 15, y, "C", 0);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Console::WriteString(int x, int y, const char *str)
{
    int numCell = y * WIDTH_CONSOLE + x;

    for(uint i = 0; i < strlen(str); i++)
    {
        backBuffer[numCell++].Char.AsciiChar = str[i];
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Console::WriteBackBuffer()
{
    for(int i = 0; i < WIDTH_CONSOLE; i++)
    {
        backBuffer[WIDTH_CONSOLE * (HEIGHT_CONSOLE - 1) + i].Char.AsciiChar = commandLine[i];
    }

    COORD buffSize;
    buffSize.X = WIDTH_CONSOLE;
    buffSize.Y = HEIGHT_CONSOLE;

    COORD buffCoord = {0, 0};

    SMALL_RECT region;
    region.Left = 0;
    region.Top = 0;
    region.Right = WIDTH_CONSOLE - 1;
    region.Bottom = HEIGHT_CONSOLE - 1;

    WriteConsoleOutputA(outHandle, backBuffer, buffSize, buffCoord, &region);
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


//------------------------------------------------------------------------------------------------------------------------------------------------------
char* Console::WriteBinaryByte(int value)
{
    static char buffer[11] = "          ";

    vector<uint8> bits;

    for(int i = 0; i < 8; i++)
    {
        bits.push_back((uint8)(value % 2));
        value /= 2;
    }

    buffer[0] = bits[7] + 0x30;
    buffer[1] = bits[6] + 0x30;
    buffer[3] = bits[5] + 0x30;
    buffer[4] = bits[4] + 0x30;
    buffer[5] = bits[3] + 0x30;
    buffer[7] = bits[2] + 0x30;
    buffer[8] = bits[1] + 0x30;
    buffer[9] = bits[0] + 0x30;

    return buffer;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Console::WriteListing()
{
    vector<Command> &commands = base.GetCommands();
    
    static char buffer[1024];

    uint numCommand = 0;

    for(size_t i = 0; i < HEIGHT_CONSOLE - 7; i++)
    {
        Command &command = commands[numCommand++];
        sprintf_s(buffer, 100, "%04X | ", command.address);
        sprintf_s(buffer + strlen(buffer), 100, "%02X | ", command.opCodes[0]);
        sprintf_s(buffer + strlen(buffer), 100, "%s | ", WriteBinaryByte(command.opCodes[0]));
        if(command.bad)
        {
            sprintf_s(buffer + strlen(buffer), 100, "ERROR!!! BAD COMMAND!!! ERROR!!!!!!!");
        }
        else
        {
            sprintf_s(buffer + strlen(buffer), 100, "%s", command.mnemonic.c_str());
        }

        WriteString(0, (int)i, buffer);

        for(uint numCode = 1; numCode < command.opCodes.size(); numCode++)
        {
            i++;
            sprintf_s(buffer, 100, "     | %02X | ", command.opCodes[numCode]);
            sprintf_s(buffer + strlen(buffer), 100, "%s |", WriteBinaryByte(command.opCodes[numCode]));
            WriteString(0, (int)i, buffer);
        }
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Console::ClearBackBuffer()
{
    for(int i = 0; i < WIDTH_CONSOLE * HEIGHT_CONSOLE; i++)
    {
        backBuffer[i].Char.AsciiChar = ' ';
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Console::RunCommand()
{
    if(strcmp(ExtractCommand(), "help") == 0)
    {
        ClearCommandLine();
    }
    else
    {
        ShowHint();
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
char *Console::ExtractCommand()
{
    static char buffer[WIDTH_CONSOLE + 1];

    int i = 0;

    while(commandLine[i] != '_')
    {
        buffer[i++] = commandLine[i];
    }

    buffer[i] = 0;

    return buffer;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Console::ClearCommandLine()
{
    posCommandLine = 0;

    commandLine[0] = '_';
    for(int i = 1; i < WIDTH_CONSOLE; i++)
    {
        commandLine[i] = ' ';
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Console::ShowHint()
{

}
