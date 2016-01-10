#pragma once


class Console
{
public:
    Console();

    bool Update();

private:
    HANDLE outHandle;
#define WIDTH_CONSOLE   150
#define HEIGHT_CONSOLE  80
    int posCommandLine = 0;

    DWORD prevUpdate;

    void AddToCommandLine(char symbol);
    void WriteString(int x, int y, const char *str);
    void WriteScreen();
    void Write4bit(int x, int y, uint8 byte);
    void Write8bit(int x, int y, uint8 byte);
    void Write16bit(int x, int y, uint16 word);
    void WriteFlags(int x, int y);
    void WriteRegisters(int dY);
    void WriteListing();
    char* WriteBinaryByte(int value);
    void ClearBackBuffer();
    void WriteBackBuffer();

    CHAR_INFO backBuffer[WIDTH_CONSOLE * HEIGHT_CONSOLE];

    char commandLine[WIDTH_CONSOLE];

    Console &operator=(const Console&)
    {};
};
