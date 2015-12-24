#include "defines.h"
#include "RAM.h"
#include "registers.h"
#include "Timer.h"
#include "InstructionSet.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RunCommand(void);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    /*
    Сначала настроим таймер тиков таким образом, чтобы он отсчитывал нам тики.
    */

    RAM[0] = 1;
    
    Timer_Init();

    Timer_StartTicks();

    while(true)
    {
        uint tackts = RunCommand();
        Timer_WaitForNTacts(tackts);
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
// Executes the command for address
// Return the number of tackts
int RunCommand(void)
{
    uint8 memValue = GetFromPCandInc();

    if((memValue & BINARY_U8(11000000)) == BINARY_U8(01000000))
    {
        LD_R_R(memValue);
    }
    else if((memValue & BINARY_U8(00000110)) == BINARY_U8(00000110))
    {
        LD_R_N(memValue);
    }
    else if(memValue == 0xdd)
    {
        RunCommandWithPrefixDD();
    }

    return 0;
}
