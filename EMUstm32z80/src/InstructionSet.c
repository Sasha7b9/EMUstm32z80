#include "InstructionSet.h"
#include "registers.h"
#include "RAM.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Extract register8 from bits 0...2
static REG_8 Reg8Lo(uint8 value)
{
    return (REG_8)(value & 7);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
// Ettract registers8 from bits 3...5
static REG_8 Reg8Hi(uint value)
{
    return (REG_8)((value >> 3) & 7);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_R_R(uint8 memValue)
{
    REG_8 dest = Reg8Hi(memValue);
    REG_8 src = Reg8Lo(memValue);

    LoadReg8(dest, GetReg8(src));

    return 4;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_R_N(uint8 memValue)
{
    REG_8 dest = Reg8Hi(memValue);

    LoadReg8(dest, GetFromPCandInc());

    return 7;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RunCommandWithPrefixDD(void)
{
    uint8 memValue = GetFromPCandInc();
}
