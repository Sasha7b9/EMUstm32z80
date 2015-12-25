#include "instrED.h"

#include "defines.h"

int RunCommandWithPrefixED(void)
{
    const pFuncIV secondLevel[256] =
    {
        /*   00 000 000   */ 0,
        /*   00 000 001   */ 0,
        /*   00 000 010   */ 0,
        /*   00 000 011   */ 0,
        /*   00 000 100   */ NEG,
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
        /*   00 100 001   */ 0,
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
        /*   00 110 100   */ 0,
        /*   00 110 101   */ 0,
        /*   00 110 110   */ 0,
        /*   00 110 111   */ 0,
        /*   00 111 000   */ 0,
        /*   00 111 001   */ 0,
        /*   00 111 010   */ 0,
        /*   00 111 011   */ 0,
        /*   00 111 100   */ 0,
        /*   00 111 101   */ 0,
        /*   00 111 110   */ 0,
        /*   00 111 111   */ 0,
        /*   01 000 000   */ IN_R_pC,
        /*   01 000 001   */ OUT_pC_R,
        /*   01 000 010   */ SBC_HL_SS,
        /*   01 000 011   */ LD_pNN_DD,
        /*   01 000 100   */ 0,
        /*   01 000 101   */ RETN,
        /*   01 000 110   */ IM0,
        /*   01 000 111   */ LD_I_A,
        /*   01 001 000   */ IN_R_pC,
        /*   01 001 001   */ OUT_pC_R,
        /*   01 001 010   */ ADC_HL_SS,
        /*   01 001 011   */ LD_DD_pNN,
        /*   01 001 100   */ 0,
        /*   01 001 101   */ 0,
        /*   01 001 110   */ 0,
        /*   01 001 111   */ LD_R_A,
        /*   01 010 000   */ IN_R_pC,
        /*   01 010 001   */ 0,
        /*   01 010 010   */ SBC_HL_SS,
        /*   01 010 011   */ LD_pNN_DD,
        /*   01 010 100   */ 0,
        /*   01 010 101   */ 0,
        /*   01 010 110   */ IM1,
        /*   01 010 111   */ LD_A_I,
        /*   01 011 000   */ IN_R_pC,
        /*   01 011 001   */ 0,
        /*   01 011 010   */ ADC_HL_SS,
        /*   01 011 011   */ LD_DD_pNN,
        /*   01 011 100   */ 0,
        /*   01 011 101   */ 0,
        /*   01 011 110   */ IM2,
        /*   01 011 111   */ LD_A_R,
        /*   01 100 000   */ IN_R_pC,
        /*   01 100 001   */ 0,
        /*   01 100 010   */ SBC_HL_SS,
        /*   01 100 011   */ LD_pNN_DD,
        /*   01 100 100   */ 0,
        /*   01 100 101   */ 0,
        /*   01 100 110   */ 0,
        /*   01 100 111   */ RRD,
        /*   01 101 000   */ IN_R_pC,
        /*   01 101 001   */ 0,
        /*   01 101 010   */ ADC_HL_SS,
        /*   01 101 011   */ LD_DD_pNN,
        /*   01 101 100   */ 0,
        /*   01 101 101   */ 0,
        /*   01 101 110   */ 0,
        /*   01 101 111   */ RLD,
        /*   01 110 000   */ IN_R_pC,
        /*   01 110 001   */ 0,
        /*   01 110 010   */ SBC_HL_SS,
        /*   01 110 011   */ LD_pNN_DD,
        /*   01 110 100   */ 0,
        /*   01 110 101   */ 0,
        /*   01 110 110   */ 0,
        /*   01 110 111   */ 0,
        /*   01 111 000   */ IN_R_pC,
        /*   01 111 001   */ 0,
        /*   01 111 010   */ ADC_HL_SS,
        /*   01 111 011   */ LD_DD_pNN,
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
        /*   10 010 110   */ 0,
        /*   10 010 111   */ 0,
        /*   10 011 000   */ 0,
        /*   10 011 001   */ 0,
        /*   10 011 010   */ 0,
        /*   10 011 011   */ 0,
        /*   10 011 100   */ 0,
        /*   10 011 101   */ 0,
        /*   10 011 110   */ 0,
        /*   10 011 111   */ 0,
        /*   10 100 000   */ LDI,
        /*   10 100 001   */ CPI,
        /*   10 100 010   */ INI,
        /*   10 100 011   */ 0,
        /*   10 100 100   */ 0,
        /*   10 100 101   */ 0,
        /*   10 100 110   */ 0,
        /*   10 100 111   */ 0,
        /*   10 101 000   */ LDD,
        /*   10 101 001   */ CPD,
        /*   10 101 010   */ IND,
        /*   10 101 011   */ 0,
        /*   10 101 100   */ 0,
        /*   10 101 101   */ 0,
        /*   10 101 110   */ 0,
        /*   10 101 111   */ 0,
        /*   10 110 000   */ 0,
        /*   10 110 001   */ CPIR,
        /*   10 110 010   */ INIR,
        /*   10 110 011   */ 0,
        /*   10 110 100   */ 0,
        /*   10 110 101   */ 0,
        /*   10 110 110   */ 0,
        /*   10 110 111   */ 0,
        /*   10 111 000   */ LDDR,
        /*   10 111 001   */ CPDR,
        /*   10 111 010   */ INDR,
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
        /*   11 001 011   */ 0,
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
        /*   11 110 000   */ LDIR,
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

    return 0;   // WARN
}
