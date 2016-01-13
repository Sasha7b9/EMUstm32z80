#pragma once


class Console;


class CommandConsole
{
public:
    CommandConsole(Console *console);

    void Run(char *command);

private:
    Console *console = nullptr;
};
