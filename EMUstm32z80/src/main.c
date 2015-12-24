#include "defines.h"
#include "RAM.h"
#include "registers.h"
#include "Timer.h"
#include "InstructionSet.h"


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
