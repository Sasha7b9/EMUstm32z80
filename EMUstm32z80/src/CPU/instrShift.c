#include "instrShift.h"


#include "registers.h"


#include "common.h"


#include <string.h>


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RLC(TypeOperand type)
{
    // + + X 0 X P 0 +

#ifdef LISTING

    if (type == Operand_A)
    {
        AddAddress(PC);
        strcpy(mnemonic, "RLCA");
        return -1;
    }
    else if(type == Operand_Reg8)
    {
        AddAddress(PC);
        sprintf(mnemonic, "RLC %s", R8_LO_Name(prevPC));
        return -1;
    }
    else if(type == Operand_pHL)
    {
        AddAddress(PC);
        strcpy(mnemonic, "RLC [HL]");
        return -1;
    }
    else if(type == Operand_IX)
    {

    }
    else if(type == Operand_IY)
    {
    }

#else 

#define RUN_RLC(t)                          \
    uint8 hiBit = GET_BIT(*pOperand, 7);    \
    (*pOperand) <<= 1;                      \
    LOAD_BIT(*pOperand, 0, hiBit);          \
    LOAD_C(hiBit);                          \
    CALC_S(*pOperand);                      \
    CALC_P(*pOperand);                      \
    RES_H;                                  \
    RES_N;                                  \
    return t;

    if (type == Operand_A)
    {
        uint8 *pOperand = &A;

        RUN_RLC(4);
    }
    else if(type == Operand_Reg8)
    {
        uint8 *pOperand = pR8_LO(prevPC);

        RUN_RLC(8);
    }
    else if (type == Operand_pHL)
    {
        uint8 *pOperand = pHL;

        RUN_RLC(15);
    }
    else if (type == Operand_IX || type == Operand_IY)
    {
        int index = ((type == Operand_IX) ? IX : IY) + PCandInc();

        uint8 *pOperand = &(RAM[index]);

        PCandInc();

        RUN_RLC(23);
    }

    return 0;

#endif
}