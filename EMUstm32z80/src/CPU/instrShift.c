#include "instrShift.h"


#include "registers.h"


#include "common.h"


#include <string.h>

#include <stdio.h>


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RLC(TypeOperand type)
{
    // + + X 0 X P 0 +

#ifdef LISTING

    AddAddress(PC);

    if (type == Operand_A)
    {
        strcpy(mnemonic, "RLCA");
        return -1;
    }
    else if(type == Operand_Reg8)
    {
        sprintf(mnemonic, "RLC %s", R8_LO_Name(prevPC));
        return -1;
    }
    else if(type == Operand_pHL)
    {
        strcpy(mnemonic, "RLC [HL]");
    }
    else
    {
        char *name = type == Operand_IX ? "IX" : "IY";

        if (RAM[PC - 1] == 0x06)
        {
            sprintf(mnemonic, "RLC [%s+%02X]", name, RAM[PC - 2]);
        }
        else
        {
            sprintf(mnemonic, "RLC [%s+%02X]->", name, RAM[PC - 2], R8_LO_Name(RAM[PC - 2]));
        }
    }
    return -1;

#else 

#define RUN_RLC()                           \
    uint8 hiBit = GET_BIT(*pOperand, 7);    \
    (*pOperand) <<= 1;                      \
    LOAD_BIT(*pOperand, 0, hiBit);          \
    LOAD_C(hiBit);                          \
    CALC_S(*pOperand);                      \
    CALC_P(*pOperand);                      \
    RES_H;                                  \
    RES_N;

    if (type == Operand_A)
    {
        uint8 *pOperand = &A;

        RUN_RLC();

        return 4;
    }
    else if(type == Operand_Reg8)
    {
        uint8 *pOperand = pR8_LO(prevPC);

        RUN_RLC();

        return 8;
    }
    else if (type == Operand_pHL)
    {
        uint8 *pOperand = &pHL;

        RUN_RLC();

        return 15;
    }
    else if (type == Operand_IX || type == Operand_IY)
    {
        int index = ((type == Operand_IX) ? IX : IY) + RAM[PC - 2];

        uint8 *pOperand = &(RAM[index]);

        RUN_RLC();

        if (RAM[PC - 1] != 0x06)
        {
            R8_LO(RAM[PC - 1]) = *pOperand;
        }

        return 23;
    }

    return 0;

#endif
}