#include "defines.h"
#include "Timer.h"
#include "InstructionSet.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    /*
    ������� �������� ������ ����� ����� �������, ����� �� ���������� ��� ����.
    */

    Timer_Init();

    Timer_StartTicks();

//    while(true)
//    {
        uint tackts = RunCommand();
        Timer_WaitForNTacts(tackts);
//    }
}
