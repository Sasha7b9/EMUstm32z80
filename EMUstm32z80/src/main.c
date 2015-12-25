#include "defines.h"
#include "Timer.h"
#include "InstructionSet.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    /*
    Сначала настроим таймер тиков таким образом, чтобы он отсчитывал нам тики.
    */

    Timer_Init();

    Timer_StartTicks();

//    while(true)
//    {
        uint tackts = RunCommand();
        Timer_WaitForNTacts(tackts);
//    }
}
