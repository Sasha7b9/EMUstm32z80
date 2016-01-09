#include "instrFD.h"
#include "defines.h"
#include "CPU/registers.h"
#include "Hardware/ports.h"
#include <string.h>
#include <stdio.h>
#include "common.h"
#include "RAM.h"
#include "instrFDCB_DDCB.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int INC_pIY_D(void)
{
#ifdef LISTING

    AddOpcode(RAM8(PC));
    sprintf(mnemonic, "INC [IY+%02X]", PCandInc());
    AddAddress(PC);
    return -1;

#else

    return 0;

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

    return 0;

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

    return 0;

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

    return 0;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int SET_B_pIY_D_RES_pIY_D_BIT_B_pIY_D(void)
{
    return RunThridLevel(IR_IY);

    /*
#ifdef LISTING

    AddOpcode(RAM8(PC));
    AddOpcode(RAM8(PC + 1));
    AddAddress(PC + 2);

    uint8 valD = PCandInc();
    uint8 valBit = PCandInc();
    uint8 bit = (valBit >> 3) & 7;

    if((valBit & 0xc7) == 0xc6)       // SET B, (IY + D)
    {
        sprintf(mnemonic, "SET %d,[IY+%02X]", bit, valD);
        return -1;
    }
    else if((valBit & 0xc7) == 0x86)  // RES B, (IY + D)
    {
        sprintf(mnemonic, "RES %d,[IY+%02X]", bit, valD);
        return -1;
    }
    else if((valBit & 0xc7) == 0x46)  // BIT B, (IY + D)
    {
        sprintf(mnemonic, "BIT %d,[IY+%02X]", bit, valD);
        return -1;
    }

    return 1;

#else

    return 0;

#endif
    */
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

    sprintf(mnemonic, "LD [IY+%02X],%02X", valD, valN);

    return -1;

#else

    return 0;

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

    return 0;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_R_pIY_D(void)
{
#ifdef LISTING

    uint8 valReg = prevPC;
    AddOpcode(RAM8(PC));
    AddAddress(PC + 1);
    sprintf(mnemonic, "LD %s,[IY+%02X]", R8_HI_Name(valReg), PCandInc());
    return -1;

#else

    return 0;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int ADD_A_pIY_D(void)
{
#ifdef LISTING

    AddOpcode(RAM8(PC));
    AddAddress(PC + 1);
    sprintf(mnemonic, "ADD A,[IY+%02X]", prevPC);
    return -1;

#else

    return 0;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int CP_pIY_D(void)
{
#ifdef LISTING

    AddAddress(PC + 1);
    AddOpcode(RAM8(PC));
    sprintf(mnemonic, "CP [IY+%02X]", PCandInc());
    return -1;

#else

    return 0;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int XOR_pIY_D(void)
{
#ifdef LISTING

    AddOpcode(RAM8(PC + 1));
    AddAddress(PC + 1);
    sprintf(mnemonic, "XOR [IY+%02X]", PCandInc());
    return -1;

#else

    return 0;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
#include "FuncSecondFD.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RunCommandWithPrefixFD(void)
{
    AddOpcode(RAM8(PC));

    int index = PCandInc();

    if(secondLevelFD[index][0] == 0)
    {
        return 0;
    }

    return secondLevelFD[index][0]();
}
