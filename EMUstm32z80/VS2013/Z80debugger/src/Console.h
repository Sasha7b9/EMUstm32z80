#pragma once


class Console
{
public:
    Console();

    bool Update();

private:
    HANDLE outHandle;
    const SHORT WIDTH = 150;
    const SHORT HEIGHT = 80;
    int posCommandLine = 0;

    DWORD prevUpdate;

    void AddToCommandLine(char symbol);
    void WriteString(int x, int y, char *str);
    void WriteRegisters();
    void Write4bit(int x, int y, uint8 byte);
    void Write8bit(int x, int y, uint8 byte);
    void Write16bit(int x, int y, uint16 word);
    void WriteFlags(int x, int y);

    Console &operator=(const Console&)
    {};
};
