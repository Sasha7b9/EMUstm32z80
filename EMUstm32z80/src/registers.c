#include "registers.h"
#include "RAM.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static uint16 regPC = 0;

static uint8 prevRegPC = 0;

static uint8 regs8[10] = {0};

static uint16 regHL = 0;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
uint16 GetReg16(REG_16 reg)
{
    if(reg == RPC)
    {
        return regPC;
    }
    
    return 0;
}
*/


//------------------------------------------------------------------------------------------------------------------------------------------------------
uint8 GetFromPCandInc(void)
{
    prevRegPC = RAM[regPC];
    regPC++;
    return prevRegPC;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
uint8 GetPrevPC(void)
{
    return prevRegPC;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
uint8 GetReg8(REG_8 reg)
{
    if(reg == RpHL)
    {
        return RAM[regHL];
    }
    return regs8[reg];
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void LoadReg8(REG_8 dest, uint8 value)
{
    if(dest == RpHL)
    {
        RAM[regHL] = value;
    }
    else
    {
        regs8[dest] = value;
    }
}
