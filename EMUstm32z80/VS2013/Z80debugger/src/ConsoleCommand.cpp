#include "stdafx.h"


#include "ConsoleCommand.h"
#include "Console.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CommandConsole::CommandConsole(Console *console)
{
    this->console = console;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void CommandConsole::Run(char *command)
{
    strings.push_back(command);

    if(strcmp(command, "help") == 0 || strcmp(command, "?") == 0)
    {
        console->ClearCommandLine();
    }
    else if(strcmp(command, "exit") == 0)
    {
        console->running = false;
    }
    else
    {
        console->ShowHint();
        strings.pop_back();
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void CommandConsole::ShowNext()
{

}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void CommandConsole::ShowPrev()
{

}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void CommandConsole::AddNewCommand()
{

}
