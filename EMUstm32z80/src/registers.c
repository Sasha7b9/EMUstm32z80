#include "registers.h"
#include "RAM.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static uint16 regPC = 0;

static uint16 regSP = 0;

static uint8 prevRegPC = 0;

static uint8 regs8[11] = {0};

static uint8 regs8alt[11] = {0};

static uint16 regHL = 0;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint16 GetRegQQ(REG_QQ reg)
{
    if(reg == RQQ_BC)
    {
        return regs8[RB] * 256 + regs8[RC];
    }

    if(reg == RQQ_DE)
    {
        return regs8[RD] * 256 + regs8[RE];
    }

    if(reg == RQQ_HL)
    {
        return regs8[RH] * 256 + regs8[RL];
    }

    if(reg == RQQ_AF)
    {
        return regs8[RA] * 256 + regs8[RF];
    }

    return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
uint16 GetRegDD(REG_DD reg)
{
    if(reg == RDD_BC)
    {
        return GetRegQQ(RQQ_BC);
    }

    if(reg == RDD_DE)
    {
        return GetRegQQ(RQQ_DE);
    }

    if(reg == RDD_HL)
    {
        return GetRegQQ(RQQ_HL);
    }

    if(reg == RDD_SP)
    {
        return regSP;
    }

    return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void LoadRegDD(REG_DD reg, uint16 value)
{
    if(reg == RDD_BC)
    {
        regs8[RC] = (uint8)value;
        regs8[RB] = (uint8)(value >> 8);
    }
    else if(reg == RDD_DE)
    {
        regs8[RE] = (uint8)value;
        regs8[RB] = (uint8)(value >> 8);
    }
    else if(reg == RDD_HL)
    {
        regs8[RL] = (uint8)value;
        regs8[RH] = (uint8)(value >> 8);
    }
    else if(reg == RDD_SP)
    {
        regSP = value;
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void LoadRegQQ(REG_QQ reg, uint16 value)
{
    if(reg == RQQ_BC)
    {
        LoadRegDD(RDD_BC, value);
    }
    else if(reg == RQQ_DE)
    {
        LoadRegDD(RDD_DE, value);
    }
    else if(reg == RQQ_HL)
    {
        LoadRegDD(RDD_HL, value);
    }
    else if(reg == RQQ_AF)
    {
        regs8[RF] = (uint8)value;
        regs8[RA] = (uint8)(value >> 8);
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
uint8 PCandInc(void)
{
    prevRegPC = RAM[regPC];
    regPC++;
    return prevRegPC;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
uint16 PCandInc16(void)
{
    uint8 low = RAM[regPC++];
    uint8 hi = RAM[regPC++];

    return low + hi * 256;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
uint8 PrevPC(void)
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


//------------------------------------------------------------------------------------------------------------------------------------------------------
void ExchangeReg8(REG_8 reg)
{
    uint8 temp = regs8[reg];
    regs8[reg] = regs8alt[reg];
    regs8alt[reg] = temp;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
uint8 CY(void)
{
    return regs8[RF] & 0x01;
}