#include "instrCB.h"

#include "defines.h"

#include "CPU/registers.h"

#include "Hardware/ports.h"

#include <string.h>

#include <stdio.h>

#include "common.h"

#include "RAM.h"

#include "instrShift.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BIT_B_R(void)
{
#ifdef LISTING

    AddAddress(PC);
    sprintf(mnemonic, "BIT %d,%s", (prevPC >> 3) & 7, R8_LO_Name(prevPC));
    return -1;

#else

    return 0;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int CRL_R(void)
{
#ifdef LISTING

    AddAddress(PC);
    sprintf(mnemonic, "SRL %s", R8_LO_Name(prevPC));
    return -1;

#else

    return 0;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int CRL_pHL(void)
{
#ifdef LISTING

    AddAddress(PC);
    strcpy(mnemonic, "SRL [HL]");
    return -1;

#else

    return 0;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RLC_pHL(void)
{
    return RLC(Operand_pHL);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RLC_R(void)
{
    return RLC(Operand_Reg8);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RES_B_M(void)
{
#ifdef LISTING

    AddAddress(PC);
    uint8 numBit = (prevPC >> 3) & 7;
    sprintf(mnemonic, "RES %d,%s", numBit, R8_LO_Name(prevPC));
    return -1;

#else

    return 0;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RES_B_pHL(void)
{
#ifdef LISTING

    AddAddress(PC);
    uint8 numBit = (prevPC >> 3) & 7;
    sprintf(mnemonic, "RES %d,[HL]", numBit);
    return -1;

#else

    return 0;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int SET_B_R(void)
{
#ifdef LISTING

    AddAddress(PC);
    sprintf(mnemonic, "SET %d,%s", (prevPC >> 3) & 7, R8_LO_Name(prevPC));
    return -1;

#else

    return 0;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int SET_B_pHL(void)
{
#ifdef LISTING

    AddAddress(PC);
    sprintf(mnemonic, "SET %d,[HL]", (prevPC >> 3) & 7);
    return -1;

#else

    return 0;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RL_R(void)
{
#ifdef LISTING

    AddAddress(PC);
    sprintf(mnemonic, "RL %s", R8_LO_Name(prevPC));
    return -1;

#else

    return 0;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RR_R(void)
{
#ifdef LISTING

    AddAddress(PC);
    sprintf(mnemonic, "RR %s", R8_LO_Name(prevPC));
    return -1;

#else

    return 0;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
#include "SecondLevelFuncCB.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RunCommandWithPrefixCB(void)
{
    AddOpcode(RAM8(PC));

    int index = PCandInc();

    if(secondLevelCB[index][0] == 0)
    {
        return 0;
    }

    return secondLevelCB[index][0]();
}
