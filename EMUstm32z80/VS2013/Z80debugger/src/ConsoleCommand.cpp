#include "stdafx.h"


#include "ConsoleCommand.h"
#include "Console.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CommandConsole::CommandConsole(Console *console)
{
    this->console = console;
}


void CommandConsole::Run(char *command)
{
    if(strcmp(command, "help") == 0)
    {
        console->ClearCommandLine();
    }
    else
    {
        console->ShowHint();
    }
}
