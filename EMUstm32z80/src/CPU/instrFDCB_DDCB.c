#include "instrFDCB_DDCB.h"
#include "defines.h"
#include "registers.h"
#include "RAM.h"
#include "common.h"
#include "instrShift.h"

#include <string.h>

#include <stdio.h>


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static TypeIR typeIR = IR_IX;


#define OPERAND (typeIR == IR_IX ? Operand_IX : Operand_IY)


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RLC_pIR_D_R(void)
{
    return RLC(OPERAND);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RLC_pIR_D(void)
{
    return RLC(OPERAND);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RRC_pIR_D_R(void)
{
    return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RRC_pIR_D(void)
{
    return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RL_pIR_D_R(void)
{
    return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RL_pIR_D(void)
{
    return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RR_pIR_D_R(void)
{
    return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RR_pIR_D(void)
{
    return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int SLA_pIR_D_R(void)
{
    return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int SLA_pIR_D(void)
{
    return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int SRA_pIY_D_R(void)
{
    return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int SRA_pIR_D(void)
{
    return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int SLS_pIY_D_R(void)
{
    return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int SLS_pIR_D(void)
{
    return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int SRL_pIY_D_R(void)
{
    return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int SRL_pIR_D(void)
{
    return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int BIT_B_pIR_D(void)
{
    return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int BIT_B_pIY(void)
{
    return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RES_B_pIY_D_R(void)
{
    return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RES_B_pIR_D(void)
{
    return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int SET_B_pIR_D_R(void)
{
    return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int SET_B_pIR_D(void)
{
    return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
#include "FuncThird.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RunThridLevel(TypeIR type)
{
    typeIR = type;

    AddOpcode(RAM8(PC));
    PCandInc();
    AddOpcode(RAM8(PC));

    int index = PCandInc();

    if (thirdLevel[index][0] == 0)
    {
        return 0;
    }

    return thirdLevel[index][0]();
}