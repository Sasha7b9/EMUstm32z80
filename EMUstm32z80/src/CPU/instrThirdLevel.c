#include "instrThirdLeevl.h"
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
int RunThridLevel(TypeIR type)
{
    typeIR = type;

    const pFuncIV secondLevel[256] =
    {
        /*   00 000 000   */ RLC_pIR_D_R,
        /*   00 000 001   */ RLC_pIR_D_R,
        /*   00 000 010   */ RLC_pIR_D_R,
        /*   00 000 011   */ RLC_pIR_D_R,
        /*   00 000 100   */ RLC_pIR_D_R,
        /*   00 000 101   */ RLC_pIR_D_R,
        /*   00 000 110   */ RLC_pIR_D,
        /*   00 000 111   */ RLC_pIR_D_R,
        /*   00 001 000   */ RRC_pIR_D_R,
        /*   00 001 001   */ RRC_pIR_D_R,
        /*   00 001 010   */ RRC_pIR_D_R,
        /*   00 001 011   */ RRC_pIR_D_R,
        /*   00 001 100   */ RRC_pIR_D_R,
        /*   00 001 101   */ RRC_pIR_D_R,
        /*   00 001 110   */ RRC_pIR_D,
        /*   00 001 111   */ RRC_pIR_D_R,
        /*   00 010 000   */ RL_pIR_D_R,
        /*   00 010 001   */ RL_pIR_D_R,
        /*   00 010 010   */ RL_pIR_D_R,
        /*   00 010 011   */ RL_pIR_D_R,
        /*   00 010 100   */ RL_pIR_D_R,
        /*   00 010 101   */ RL_pIR_D_R,
        /*   00 010 110   */ RL_pIR_D,
        /*   00 010 111   */ RL_pIR_D_R,
        /*   00 011 000   */ RR_pIR_D_R,
        /*   00 011 001   */ RR_pIR_D_R,
        /*   00 011 010   */ RR_pIR_D_R,
        /*   00 011 011   */ RR_pIR_D_R,
        /*   00 011 100   */ RR_pIR_D_R,
        /*   00 011 101   */ RR_pIR_D_R,
        /*   00 011 110   */ RR_pIR_D,
        /*   00 011 111   */ RR_pIR_D_R,
        /*   00 100 000   */ SLA_pIR_D_R,
        /*   00 100 001   */ SLA_pIR_D_R,
        /*   00 100 010   */ SLA_pIR_D_R,
        /*   00 100 011   */ SLA_pIR_D_R,
        /*   00 100 100   */ SLA_pIR_D_R,
        /*   00 100 101   */ SLA_pIR_D_R,
        /*   00 100 110   */ SLA_pIR_D,
        /*   00 100 111   */ SLA_pIR_D_R,
        /*   00 101 000   */ SRA_pIY_D_R,
        /*   00 101 001   */ SRA_pIY_D_R,
        /*   00 101 010   */ SRA_pIY_D_R,
        /*   00 101 011   */ SRA_pIY_D_R,
        /*   00 101 100   */ SRA_pIY_D_R,
        /*   00 101 101   */ SRA_pIY_D_R,
        /*   00 101 110   */ SRA_pIR_D,
        /*   00 101 111   */ SRA_pIY_D_R,
        /*   00 110 000   */ SLS_pIY_D_R,
        /*   00 110 001   */ SLS_pIY_D_R,
        /*   00 110 010   */ SLS_pIY_D_R,
        /*   00 110 011   */ SLS_pIY_D_R,
        /*   00 110 100   */ SLS_pIY_D_R,
        /*   00 110 101   */ SLS_pIY_D_R,
        /*   00 110 110   */ SLS_pIR_D,
        /*   00 110 111   */ SLS_pIY_D_R,
        /*   00 111 000   */ SRL_pIY_D_R,
        /*   00 111 001   */ SRL_pIY_D_R,
        /*   00 111 010   */ SRL_pIY_D_R,
        /*   00 111 011   */ SRL_pIY_D_R,
        /*   00 111 100   */ SRL_pIY_D_R,
        /*   00 111 101   */ SRL_pIY_D_R,
        /*   00 111 110   */ SRL_pIR_D,
        /*   00 111 111   */ SRL_pIY_D_R,
        /*   01 000 000   */ BIT_B_pIR_D,
        /*   01 000 001   */ BIT_B_pIR_D,
        /*   01 000 010   */ BIT_B_pIR_D,
        /*   01 000 011   */ BIT_B_pIR_D,
        /*   01 000 100   */ BIT_B_pIR_D,
        /*   01 000 101   */ BIT_B_pIR_D,
        /*   01 000 110   */ BIT_B_pIR_D,
        /*   01 000 111   */ BIT_B_pIR_D,
        /*   01 001 000   */ BIT_B_pIR_D,
        /*   01 001 001   */ BIT_B_pIR_D,
        /*   01 001 010   */ BIT_B_pIR_D,
        /*   01 001 011   */ BIT_B_pIR_D,
        /*   01 001 100   */ BIT_B_pIR_D,
        /*   01 001 101   */ BIT_B_pIR_D,
        /*   01 001 110   */ BIT_B_pIR_D,
        /*   01 001 111   */ BIT_B_pIR_D,
        /*   01 010 000   */ BIT_B_pIR_D,
        /*   01 010 001   */ BIT_B_pIR_D,
        /*   01 010 010   */ BIT_B_pIR_D,
        /*   01 010 011   */ BIT_B_pIR_D,
        /*   01 010 100   */ BIT_B_pIR_D,
        /*   01 010 101   */ BIT_B_pIR_D,
        /*   01 010 110   */ BIT_B_pIR_D,
        /*   01 010 111   */ BIT_B_pIR_D,
        /*   01 011 000   */ BIT_B_pIR_D,
        /*   01 011 001   */ BIT_B_pIR_D,
        /*   01 011 010   */ BIT_B_pIR_D,
        /*   01 011 011   */ BIT_B_pIR_D,
        /*   01 011 100   */ BIT_B_pIR_D,
        /*   01 011 101   */ BIT_B_pIR_D,
        /*   01 011 110   */ BIT_B_pIR_D,
        /*   01 011 111   */ BIT_B_pIR_D,
        /*   01 100 000   */ BIT_B_pIR_D,
        /*   01 100 001   */ BIT_B_pIR_D,
        /*   01 100 010   */ BIT_B_pIR_D,
        /*   01 100 011   */ BIT_B_pIR_D,
        /*   01 100 100   */ BIT_B_pIR_D,
        /*   01 100 101   */ BIT_B_pIR_D,
        /*   01 100 110   */ BIT_B_pIR_D,
        /*   01 100 111   */ BIT_B_pIR_D,
        /*   01 101 000   */ BIT_B_pIR_D,
        /*   01 101 001   */ BIT_B_pIR_D,
        /*   01 101 010   */ BIT_B_pIR_D,
        /*   01 101 011   */ BIT_B_pIR_D,
        /*   01 101 100   */ BIT_B_pIR_D,
        /*   01 101 101   */ BIT_B_pIR_D,
        /*   01 101 110   */ BIT_B_pIR_D,
        /*   01 101 111   */ BIT_B_pIR_D,
        /*   01 110 000   */ BIT_B_pIR_D,
        /*   01 110 001   */ BIT_B_pIR_D,
        /*   01 110 010   */ BIT_B_pIR_D,
        /*   01 110 011   */ BIT_B_pIR_D,
        /*   01 110 100   */ BIT_B_pIR_D,
        /*   01 110 101   */ BIT_B_pIR_D,
        /*   01 110 110   */ BIT_B_pIR_D,
        /*   01 110 111   */ BIT_B_pIR_D,
        /*   01 111 000   */ BIT_B_pIR_D,
        /*   01 111 001   */ BIT_B_pIR_D,
        /*   01 111 010   */ BIT_B_pIR_D,
        /*   01 111 011   */ BIT_B_pIR_D,
        /*   01 111 100   */ BIT_B_pIR_D,
        /*   01 111 101   */ BIT_B_pIR_D,
        /*   01 111 110   */ BIT_B_pIR_D,
        /*   01 111 111   */ BIT_B_pIR_D,
        /*   10 000 000   */ RES_B_pIY_D_R,
        /*   10 000 001   */ RES_B_pIY_D_R,
        /*   10 000 010   */ RES_B_pIY_D_R,
        /*   10 000 011   */ RES_B_pIY_D_R,
        /*   10 000 100   */ RES_B_pIY_D_R,
        /*   10 000 101   */ RES_B_pIY_D_R,
        /*   10 000 110   */ RES_B_pIR_D,
        /*   10 000 111   */ RES_B_pIY_D_R,
        /*   10 001 000   */ RES_B_pIY_D_R,
        /*   10 001 001   */ RES_B_pIY_D_R,
        /*   10 001 010   */ RES_B_pIY_D_R,
        /*   10 001 011   */ RES_B_pIY_D_R,
        /*   10 001 100   */ RES_B_pIY_D_R,
        /*   10 001 101   */ RES_B_pIY_D_R,
        /*   10 001 110   */ RES_B_pIR_D,
        /*   10 001 111   */ RES_B_pIY_D_R,
        /*   10 010 000   */ RES_B_pIY_D_R,
        /*   10 010 001   */ RES_B_pIY_D_R,
        /*   10 010 010   */ RES_B_pIY_D_R,
        /*   10 010 011   */ RES_B_pIY_D_R,
        /*   10 010 100   */ RES_B_pIY_D_R,
        /*   10 010 101   */ RES_B_pIY_D_R,
        /*   10 010 110   */ RES_B_pIR_D,
        /*   10 010 111   */ RES_B_pIY_D_R,
        /*   10 011 000   */ RES_B_pIY_D_R,
        /*   10 011 001   */ RES_B_pIY_D_R,
        /*   10 011 010   */ RES_B_pIY_D_R,
        /*   10 011 011   */ RES_B_pIY_D_R,
        /*   10 011 100   */ RES_B_pIY_D_R,
        /*   10 011 101   */ RES_B_pIY_D_R,
        /*   10 011 110   */ RES_B_pIR_D,
        /*   10 011 111   */ RES_B_pIY_D_R,
        /*   10 100 000   */ RES_B_pIY_D_R,
        /*   10 100 001   */ RES_B_pIY_D_R,
        /*   10 100 010   */ RES_B_pIY_D_R,
        /*   10 100 011   */ RES_B_pIY_D_R,
        /*   10 100 100   */ RES_B_pIY_D_R,
        /*   10 100 101   */ RES_B_pIY_D_R,
        /*   10 100 110   */ RES_B_pIR_D,
        /*   10 100 111   */ RES_B_pIY_D_R,
        /*   10 101 000   */ RES_B_pIY_D_R,
        /*   10 101 001   */ RES_B_pIY_D_R,
        /*   10 101 010   */ RES_B_pIY_D_R,
        /*   10 101 011   */ RES_B_pIY_D_R,
        /*   10 101 100   */ RES_B_pIY_D_R,
        /*   10 101 101   */ RES_B_pIY_D_R,
        /*   10 101 110   */ RES_B_pIR_D,
        /*   10 101 111   */ RES_B_pIY_D_R,
        /*   10 110 000   */ RES_B_pIY_D_R,
        /*   10 110 001   */ RES_B_pIY_D_R,
        /*   10 110 010   */ RES_B_pIY_D_R,
        /*   10 110 011   */ RES_B_pIY_D_R,
        /*   10 110 100   */ RES_B_pIY_D_R,
        /*   10 110 101   */ RES_B_pIY_D_R,
        /*   10 110 110   */ RES_B_pIR_D,
        /*   10 110 111   */ RES_B_pIY_D_R,
        /*   10 111 000   */ RES_B_pIY_D_R,
        /*   10 111 001   */ RES_B_pIY_D_R,
        /*   10 111 010   */ RES_B_pIY_D_R,
        /*   10 111 011   */ RES_B_pIY_D_R,
        /*   10 111 100   */ RES_B_pIY_D_R,
        /*   10 111 101   */ RES_B_pIY_D_R,
        /*   10 111 110   */ RES_B_pIR_D,
        /*   10 111 111   */ RES_B_pIY_D_R,
        /*   11 000 000   */ SET_B_pIR_D_R,
        /*   11 000 001   */ SET_B_pIR_D_R,
        /*   11 000 010   */ SET_B_pIR_D_R,
        /*   11 000 011   */ SET_B_pIR_D_R,
        /*   11 000 100   */ SET_B_pIR_D_R,
        /*   11 000 101   */ SET_B_pIR_D_R,
        /*   11 000 110   */ SET_B_pIR_D,
        /*   11 000 111   */ SET_B_pIR_D_R,
        /*   11 001 000   */ SET_B_pIR_D_R,
        /*   11 001 001   */ SET_B_pIR_D_R,
        /*   11 001 010   */ SET_B_pIR_D_R,
        /*   11 001 011   */ SET_B_pIR_D_R,
        /*   11 001 100   */ SET_B_pIR_D_R,
        /*   11 001 101   */ SET_B_pIR_D_R,
        /*   11 001 110   */ SET_B_pIR_D,
        /*   11 001 111   */ SET_B_pIR_D_R,
        /*   11 010 000   */ SET_B_pIR_D_R,
        /*   11 010 001   */ SET_B_pIR_D_R,
        /*   11 010 010   */ SET_B_pIR_D_R,
        /*   11 010 011   */ SET_B_pIR_D_R,
        /*   11 010 100   */ SET_B_pIR_D_R,
        /*   11 010 101   */ SET_B_pIR_D_R,
        /*   11 010 110   */ SET_B_pIR_D,
        /*   11 010 111   */ SET_B_pIR_D_R,
        /*   11 011 000   */ SET_B_pIR_D_R,
        /*   11 011 001   */ SET_B_pIR_D_R,
        /*   11 011 010   */ SET_B_pIR_D_R,
        /*   11 011 011   */ SET_B_pIR_D_R,
        /*   11 011 100   */ SET_B_pIR_D_R,
        /*   11 011 101   */ SET_B_pIR_D_R,
        /*   11 011 110   */ SET_B_pIR_D,
        /*   11 011 111   */ SET_B_pIR_D_R,
        /*   11 100 000   */ SET_B_pIR_D_R,
        /*   11 100 001   */ SET_B_pIR_D_R,
        /*   11 100 010   */ SET_B_pIR_D_R,
        /*   11 100 011   */ SET_B_pIR_D_R,
        /*   11 100 100   */ SET_B_pIR_D_R,
        /*   11 100 101   */ SET_B_pIR_D_R,
        /*   11 100 110   */ SET_B_pIR_D,
        /*   11 100 111   */ SET_B_pIR_D_R,
        /*   11 101 000   */ SET_B_pIR_D_R,
        /*   11 101 001   */ SET_B_pIR_D_R,
        /*   11 101 010   */ SET_B_pIR_D_R,
        /*   11 101 011   */ SET_B_pIR_D_R,
        /*   11 101 100   */ SET_B_pIR_D_R,
        /*   11 101 101   */ SET_B_pIR_D_R,
        /*   11 101 110   */ SET_B_pIR_D,
        /*   11 101 111   */ SET_B_pIR_D_R,
        /*   11 110 000   */ SET_B_pIR_D_R,
        /*   11 110 001   */ SET_B_pIR_D_R,
        /*   11 110 010   */ SET_B_pIR_D_R,
        /*   11 110 011   */ SET_B_pIR_D_R,
        /*   11 110 100   */ SET_B_pIR_D_R,
        /*   11 110 101   */ SET_B_pIR_D_R,
        /*   11 110 110   */ SET_B_pIR_D,
        /*   11 110 111   */ SET_B_pIR_D_R,
        /*   11 111 000   */ SET_B_pIR_D_R,
        /*   11 111 001   */ SET_B_pIR_D_R,
        /*   11 111 010   */ SET_B_pIR_D_R,
        /*   11 111 011   */ SET_B_pIR_D_R,
        /*   11 111 100   */ SET_B_pIR_D_R,
        /*   11 111 101   */ SET_B_pIR_D_R,
        /*   11 111 110   */ SET_B_pIR_D,
        /*   11 111 111   */ SET_B_pIR_D_R
    };

    AddOpcode(RAM8(PC));
    PCandInc();
    AddOpcode(RAM8(PC));

    int index = PCandInc();

    if (secondLevel[index] == 0)
    {
        return 0;
    }

    return secondLevel[index]();
}