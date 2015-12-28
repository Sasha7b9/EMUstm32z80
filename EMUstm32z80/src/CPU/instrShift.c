#include "instrShift.h"


#include "registers.h"





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RLC(TypeOperand type)
{
#ifdef LISTING




    if(type == Operand_Reg8)
    {
        uint8 hiBit = GET_BIT(R8_LO(prevPC), 7);

        R8_LO(prevPC) <<= 1;
        LOAD_BIT(R8_LO(prevPC), 0, hiBit);
        LOAD_C(hiBit);

        return 8;
    }
    else if (type == Operand_pHL)
    {
        uint8 hiBit = GET_BIT(pHL, 7);

        pHL <<= 1;
        LOAD_BIT(pHL, 0, hiBit);
        LOAD_C(hiBit);

        return 15;
    }
    else if (type == Operand_IX || type == Operand_IY)
    {
        int index = ((type == Operand_IX) ? IX : IY) + PCandInc();

        uint8 *address = &(RAM[index]);

        uint8 hiBit = GET_BIT((*address), 7);

        (*address) <<= 1;
        LOAD_BIT((*address), 0, hiBit);
        LOAD_C(hiBit);

        return 23;
    }

    // + + X 0 X P 0 +

    // S
    // Z
    RES_H;
    // P
    RES_N;

#endif
}