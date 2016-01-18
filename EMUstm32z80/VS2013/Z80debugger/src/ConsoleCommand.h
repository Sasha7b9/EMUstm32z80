#pragma once


class Console;


class CommandConsole
{
public:
    CommandConsole(Console *console);

    void Run(char *command);
    void ShowNext();
    void ShowPrev();

private:
    Console *console = nullptr;
    vector<char*> strings;

    void AddNewCommand();
};
