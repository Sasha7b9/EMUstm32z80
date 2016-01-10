#include "instrShift.h"


#include "registers.h"


#include "common.h"


#include <string.h>

#include <stdio.h>


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int RLC_RRC(TypeOperand type, char *r, uint8 byte)
{
    // + + X 0 X P 0 +

#ifdef LISTING

    AddAddress(PC);

    if (type == Operand_A)
    {
        sprintf(out->mnemonic, "%sA", r);
    }
    else if (type == Operand_Reg8)
    {
        sprintf(out->mnemonic, "%s %s", r, R8_LO_Name(prevPC));
    }
    else if (type == Operand_pHL)
    {
        sprintf(out->mnemonic, "%s [HL]", r);
    }
    else
    {
        char *name = type == Operand_IX ? "IX" : "IY";

        if (RAM[PC - 1] == byte)
        {
            sprintf(out->mnemonic, "%s [%s+%02X]", r, name, RAM[PC - 2]);
        }
        else
        {
            sprintf(out->mnemonic, "%s [%s+%02X]->%s", r, name, RAM[PC - 2], R8_LO_Name(RAM[PC - 1]));
        }
    }
    return -1;

#else

#define RUN_RLC_RRC()                           \
    if(byte == 0x06)                            \
    {                                           \
        uint8 hiBit = GET_BIT(*pOperand, 7);    \
        (*pOperand) <<= 1;                      \
        LOAD_BIT(*pOperand, 0, hiBit);          \
        LOAD_C(hiBit);                          \
    }                                           \
    else                                        \
    {                                           \
        uint8 loBit = GET_BIT(*pOperand, 0);    \
        (*pOperand) >>= 1;                      \
        LOAD_BIT(*pOperand, 7, loBit);          \
        LOAD_C(loBit);                          \
    }                                           \
    CALC_S(*pOperand);                          \
    CALC_Z(*pOperand);                          \
    CALC_P(*pOperand);                          \
    RES_H;                                      \
    RES_N;

    if (type == Operand_A)
    {
        uint8 *pOperand = &A;

        RUN_RLC_RRC();

        return 4;
    }
    else if (type == Operand_Reg8)
    {
        uint8 *pOperand = pR8_LO(prevPC);

        RUN_RLC_RRC();

        return 8;
    }
    else if (type == Operand_pHL)
    {
        uint8 *pOperand = &pHL;

        RUN_RLC_RRC();

        return 15;
    }
    else if (type == Operand_IX || type == Operand_IY)
    {
        int index = ((type == Operand_IX) ? IX : IY) + RAM[PC - 2];

        uint8 *pOperand = &(RAM[index]);

        RUN_RLC_RRC();

        if (RAM[PC - 1] != byte)
        {
            R8_LO(RAM[PC - 1]) = *pOperand;
        }

        return 23;
    }

    return 0;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RLC(TypeOperand type)
{
    return RLC_RRC(type, "RLC", 0x06);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RRC(TypeOperand type)
{
    return RLC_RRC(type, "RRC", 0x0e);
}
