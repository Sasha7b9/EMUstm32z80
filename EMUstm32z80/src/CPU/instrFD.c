#include "instrFD.h"

#include "defines.h"

#include "CPU/registers.h"

#include "Hardware/ports.h"

#include <string.h>

#include <stdio.h>

#include "common.h"

#include "RAM.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int INC_pIY_D(void)
{
#ifdef LISTING

    AddOpcode(RAM8(PC));
    sprintf(mnemonic, "INC (IY+%d)", PCandInc());
    AddAddress(PC);
    return -1;

#else
#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int DEC_pIY_D(void)
{
#ifdef LISTING

    AddOpcode(RAM8(PC));
    sprintf(mnemonic, "DEC (IY+%d)", PCandInc());
    AddAddress(PC);
    return -1;

#else
#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_pIY_D_R(void)
{
#ifdef LISTING

    AddOpcode(RAM8(PC));

    char *reg = R8_LO_Name(prevPC);
    sprintf(mnemonic, "LD (IY+%d), %s", PCandInc(), reg);

    AddAddress(PC);

    return -1;

#else
#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_IY_NN(void)
{
#ifdef LISTING

    AddOpcode(RAM8(PC));
    AddOpcode(RAM8(PC + 1));

    uint16 NN = PC16andInc();

    AddAddress(PC);

    sprintf(mnemonic, "LD IY,%04x", NN);

    return -1;

#else
#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int SET_B_pIY_D_RES_pIY_D_BIT_B_pIY_D(void)
{
#ifdef LISTING

    AddOpcode(RAM8(PC));
    AddOpcode(RAM8(PC + 1));
    AddAddress(PC + 2);

    uint8 valD = PCandInc();
    uint8 valBit = PCandInc();
    uint8 bit = (valBit >> 3) & 7;

    if((valBit & 0xc7) == 0xc6)       // SET B, (IY + D)
    {
        sprintf(mnemonic, "SET %d,(IY+0x%02x)", bit, valD);
        return -1;
    }
    else if((valBit & 0xc7) == 0x86)  // RES B, (IY + D)
    {
        sprintf(mnemonic, "RES %d,(IY+0x%02x)", bit, valD);
        return -1;
    }
    else if((valBit & 0xc7) == 0x46)  // BIT B, (IY + D)
    {
        sprintf(mnemonic, "BIT %d,(IY+0x&02x)", bit, valD);
        return -1;
    }

    return 1;

#else
#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_pIY_D_N(void)
{
#ifdef LISTING

    AddOpcode(RAM8(PC));
    AddOpcode(RAM8(PC + 1));
    AddAddress(PC + 2);

    uint8 valD = PCandInc();
    uint8 valN = PCandInc();

    sprintf(mnemonic, "LD (IY+%d), %d", valD, valN);

    return -1;

#else
#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int SUB_pIY_D(void)
{
#ifdef LISTING

    AddOpcode(RAM8(PC));
    AddAddress(PC + 1);
    sprintf(mnemonic, "SUB (IY+0x%02x)", PCandInc());
    return -1;

#else

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RunCommandWithPrefixFD(void)
{
    const pFuncIV secondLevel[256] =
    {
        /*   00 000 000   */ 0,
        /*   00 000 001   */ 0,
        /*   00 000 010   */ 0,
        /*   00 000 011   */ 0,
        /*   00 000 100   */ 0,
        /*   00 000 101   */ 0,
        /*   00 000 110   */ 0,
        /*   00 000 111   */ 0,
        /*   00 001 000   */ 0,
        /*   00 001 001   */ 0,
        /*   00 001 010   */ 0,
        /*   00 001 011   */ 0,
        /*   00 001 100   */ 0,
        /*   00 001 101   */ 0,
        /*   00 001 110   */ 0,
        /*   00 001 111   */ 0,
        /*   00 010 000   */ 0,
        /*   00 010 001   */ 0,
        /*   00 010 010   */ 0,
        /*   00 010 011   */ 0,
        /*   00 010 100   */ 0,
        /*   00 010 101   */ 0,
        /*   00 010 110   */ 0,
        /*   00 010 111   */ 0,
        /*   00 011 000   */ 0,
        /*   00 011 001   */ 0,
        /*   00 011 010   */ 0,
        /*   00 011 011   */ 0,
        /*   00 011 100   */ 0,
        /*   00 011 101   */ 0,
        /*   00 011 110   */ 0,
        /*   00 011 111   */ 0,
        /*   00 100 000   */ 0,
        /*   00 100 001   */ LD_IY_NN,
        /*   00 100 010   */ 0,
        /*   00 100 011   */ 0,
        /*   00 100 100   */ 0,
        /*   00 100 101   */ 0,
        /*   00 100 110   */ 0,
        /*   00 100 111   */ 0,
        /*   00 101 000   */ 0,
        /*   00 101 001   */ 0,
        /*   00 101 010   */ 0,
        /*   00 101 011   */ 0,
        /*   00 101 100   */ 0,
        /*   00 101 101   */ 0,
        /*   00 101 110   */ 0,
        /*   00 101 111   */ 0,
        /*   00 110 000   */ 0,
        /*   00 110 001   */ 0,
        /*   00 110 010   */ 0,
        /*   00 110 011   */ 0,
        /*   00 110 100   */ INC_pIY_D,
        /*   00 110 101   */ DEC_pIY_D,
        /*   00 110 110   */ LD_pIY_D_N,
        /*   00 110 111   */ 0,
        /*   00 111 000   */ 0,
        /*   00 111 001   */ 0,
        /*   00 111 010   */ 0,
        /*   00 111 011   */ 0,
        /*   00 111 100   */ 0,
        /*   00 111 101   */ 0,
        /*   00 111 110   */ 0,
        /*   00 111 111   */ 0,
        /*   01 000 000   */ 0,
        /*   01 000 001   */ 0,
        /*   01 000 010   */ 0,
        /*   01 000 011   */ 0,
        /*   01 000 100   */ 0,
        /*   01 000 101   */ 0,
        /*   01 000 110   */ 0,
        /*   01 000 111   */ 0,
        /*   01 001 000   */ 0,
        /*   01 001 001   */ 0,
        /*   01 001 010   */ 0,
        /*   01 001 011   */ 0,
        /*   01 001 100   */ 0,
        /*   01 001 101   */ 0,
        /*   01 001 110   */ 0,
        /*   01 001 111   */ 0,
        /*   01 010 000   */ 0,
        /*   01 010 001   */ 0,
        /*   01 010 010   */ 0,
        /*   01 010 011   */ 0,
        /*   01 010 100   */ 0,
        /*   01 010 101   */ 0,
        /*   01 010 110   */ 0,
        /*   01 010 111   */ 0,
        /*   01 011 000   */ 0,
        /*   01 011 001   */ 0,
        /*   01 011 010   */ 0,
        /*   01 011 011   */ 0,
        /*   01 011 100   */ 0,
        /*   01 011 101   */ 0,
        /*   01 011 110   */ 0,
        /*   01 011 111   */ 0,
        /*   01 100 000   */ 0,
        /*   01 100 001   */ 0,
        /*   01 100 010   */ 0,
        /*   01 100 011   */ 0,
        /*   01 100 100   */ 0,
        /*   01 100 101   */ 0,
        /*   01 100 110   */ 0,
        /*   01 100 111   */ 0,
        /*   01 101 000   */ 0,
        /*   01 101 001   */ 0,
        /*   01 101 010   */ 0,
        /*   01 101 011   */ 0,
        /*   01 101 100   */ 0,
        /*   01 101 101   */ 0,
        /*   01 101 110   */ 0,
        /*   01 101 111   */ 0,
        /*   01 110 000   */ LD_pIY_D_R,
        /*   01 110 001   */ LD_pIY_D_R,
        /*   01 110 010   */ LD_pIY_D_R,
        /*   01 110 011   */ LD_pIY_D_R,
        /*   01 110 100   */ LD_pIY_D_R,
        /*   01 110 101   */ LD_pIY_D_R,
        /*   01 110 110   */ 0,
        /*   01 110 111   */ LD_pIY_D_R,
        /*   01 111 000   */ 0,
        /*   01 111 001   */ 0,
        /*   01 111 010   */ 0,
        /*   01 111 011   */ 0,
        /*   01 111 100   */ 0,
        /*   01 111 101   */ 0,
        /*   01 111 110   */ 0,
        /*   01 111 111   */ 0,
        /*   10 000 000   */ 0,
        /*   10 000 001   */ 0,
        /*   10 000 010   */ 0,
        /*   10 000 011   */ 0,
        /*   10 000 100   */ 0,
        /*   10 000 101   */ 0,
        /*   10 000 110   */ 0,
        /*   10 000 111   */ 0,
        /*   10 001 000   */ 0,
        /*   10 001 001   */ 0,
        /*   10 001 010   */ 0,
        /*   10 001 011   */ 0,
        /*   10 001 100   */ 0,
        /*   10 001 101   */ 0,
        /*   10 001 110   */ 0,
        /*   10 001 111   */ 0,
        /*   10 010 000   */ 0,
        /*   10 010 001   */ 0,
        /*   10 010 010   */ 0,
        /*   10 010 011   */ 0,
        /*   10 010 100   */ 0,
        /*   10 010 101   */ 0,
        /*   10 010 110   */ SUB_pIY_D,
        /*   10 010 111   */ 0,
        /*   10 011 000   */ 0,
        /*   10 011 001   */ 0,
        /*   10 011 010   */ 0,
        /*   10 011 011   */ 0,
        /*   10 011 100   */ 0,
        /*   10 011 101   */ 0,
        /*   10 011 110   */ 0,
        /*   10 011 111   */ 0,
        /*   10 100 000   */ 0,
        /*   10 100 001   */ 0,
        /*   10 100 010   */ 0,
        /*   10 100 011   */ 0,
        /*   10 100 100   */ 0,
        /*   10 100 101   */ 0,
        /*   10 100 110   */ 0,
        /*   10 100 111   */ 0,
        /*   10 101 000   */ 0,
        /*   10 101 001   */ 0,
        /*   10 101 010   */ 0,
        /*   10 101 011   */ 0,
        /*   10 101 100   */ 0,
        /*   10 101 101   */ 0,
        /*   10 101 110   */ 0,
        /*   10 101 111   */ 0,
        /*   10 110 000   */ 0,
        /*   10 110 001   */ 0,
        /*   10 110 010   */ 0,
        /*   10 110 011   */ 0,
        /*   10 110 100   */ 0,
        /*   10 110 101   */ 0,
        /*   10 110 110   */ 0,
        /*   10 110 111   */ 0,
        /*   10 111 000   */ 0,
        /*   10 111 001   */ 0,
        /*   10 111 010   */ 0,
        /*   10 111 011   */ 0,
        /*   10 111 100   */ 0,
        /*   10 111 101   */ 0,
        /*   10 111 110   */ 0,
        /*   10 111 111   */ 0,
        /*   11 000 000   */ 0,
        /*   11 000 001   */ 0,
        /*   11 000 010   */ 0,
        /*   11 000 011   */ 0,
        /*   11 000 100   */ 0,
        /*   11 000 101   */ 0,
        /*   11 000 110   */ 0,
        /*   11 000 111   */ 0,
        /*   11 001 000   */ 0,
        /*   11 001 001   */ 0,
        /*   11 001 010   */ 0,
        /*   11 001 011   */ SET_B_pIY_D_RES_pIY_D_BIT_B_pIY_D,
        /*   11 001 100   */ 0,
        /*   11 001 101   */ 0,
        /*   11 001 110   */ 0,
        /*   11 001 111   */ 0,
        /*   11 010 000   */ 0,
        /*   11 010 001   */ 0,
        /*   11 010 010   */ 0,
        /*   11 010 011   */ 0,
        /*   11 010 100   */ 0,
        /*   11 010 101   */ 0,
        /*   11 010 110   */ 0,
        /*   11 010 111   */ 0,
        /*   11 011 000   */ 0,
        /*   11 011 001   */ 0,
        /*   11 011 010   */ 0,
        /*   11 011 011   */ 0,
        /*   11 011 100   */ 0,
        /*   11 011 101   */ 0,
        /*   11 011 110   */ 0,
        /*   11 011 111   */ 0,
        /*   11 100 000   */ 0,
        /*   11 100 001   */ 0,
        /*   11 100 010   */ 0,
        /*   11 100 011   */ 0,
        /*   11 100 100   */ 0,
        /*   11 100 101   */ 0,
        /*   11 100 110   */ 0,
        /*   11 100 111   */ 0,
        /*   11 101 000   */ 0,
        /*   11 101 001   */ 0,
        /*   11 101 010   */ 0,
        /*   11 101 011   */ 0,
        /*   11 101 100   */ 0,
        /*   11 101 101   */ 0,
        /*   11 101 110   */ 0,
        /*   11 101 111   */ 0,
        /*   11 110 000   */ 0,
        /*   11 110 001   */ 0,
        /*   11 110 010   */ 0,
        /*   11 110 011   */ 0,
        /*   11 110 100   */ 0,
        /*   11 110 101   */ 0,
        /*   11 110 110   */ 0,
        /*   11 110 111   */ 0,
        /*   11 111 000   */ 0,
        /*   11 111 001   */ 0,
        /*   11 111 010   */ 0,
        /*   11 111 011   */ 0,
        /*   11 111 100   */ 0,
        /*   11 111 101   */ 0,
        /*   11 111 110   */ 0,
        /*   11 111 111   */ 0
    };

    AddOpcode(RAM8(PC));

    int index = PCandInc();

    if(secondLevel[index] == 0)
    {
        return 0;
    }

    return secondLevel[index]();
}
