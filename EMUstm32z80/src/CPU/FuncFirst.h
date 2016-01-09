#pragma once


const pFuncIV firstLevel[256][2] =
{
    /*   00 000 000   */    {NOP_dec,           NOP_run},
    /*   00 000 001   */    {LD_DD_NN_dec,      LD_DD_NN_run},
    /*   00 000 010   */    {LD_pBC_A_dec,      LD_pBC_A_run},
    /*   00 000 011   */    {INC_SS_dec,        INC_SS_run},
    /*   00 000 100   */    {INC_R_dec,         INC_R_run},
    /*   00 000 101   */    {DEC_M_dec,         DEC_M_run},
    /*   00 000 110   */    {LD_R_N_dec,        LD_R_N_run},
    /*   00 000 111   */    {RLCA_dec,          RLCA_run},
    /*   00 001 000   */    {EX_AF_AFalt_dec,   EX_AF_AFlat_run},
    /*   00 001 001   */    {ADD_HL_SS_dec,     ADD_HL_SS_run},
    /*   00 001 010   */    {LD_A_pBC_dec,      LD_A_pBC_run},
    /*   00 001 011   */    {DEC_SS_dec,        DEC_SS_run},
    /*   00 001 100   */    {INC_R_dec,         INC_R_run},
    /*   00 001 101   */    {DEC_M_dec,         DEC_M_run},
    /*   00 001 110   */    {LD_R_N_dec,        LD_R_N_run},
    /*   00 001 111   */    {RRCA_dec,          RRCA_run},
    /*   00 010 000   */    {DJNZ_E_dec,        DJNZ_E_run},
    /*   00 010 001   */    {LD_DD_NN_dec,      LD_DD_NN_run},
    /*   00 010 010   */    {LD_pDE_A_dec,      LD_pDE_A_run},
    /*   00 010 011   */    {INC_SS_dec,        INC_SS_run},
    /*   00 010 100   */    {INC_R_dec,         INC_R_run},
    /*   00 010 101   */    {DEC_M_dec,         DEC_M_run},
    /*   00 010 110   */    {LD_R_N_dec,        LD_R_N_run},
    /*   00 010 111   */    {RLA_dec,           RLA_run},
    /*   00 011 000   */    {JR_E_dec,          JR_E_run},
    /*   00 011 001   */    {ADD_HL_SS_dec,     ADD_HL_SS_run},
    /*   00 011 010   */    {LD_A_pDE_dec,      LD_A_pDE_run},
    /*   00 011 011   */    {DEC_SS_dec,        DEC_SS_run},
    /*   00 011 100   */    {INC_R_dec,         INC_R_run},
    /*   00 011 101   */    {DEC_M_dec,         DEC_M_run},
    /*   00 011 110   */    {LD_R_N_dec,        LD_R_N_run},
    /*   00 011 111   */    {RRA_dec,           RRA_run},
    /*   00 100 000   */    {JR_NZ_E_dec,       JR_NZ_E_run},
    /*   00 100 001   */    {LD_DD_NN_dec,      LD_DD_NN_run},
    /*   00 100 010   */    {LD_pNN_HL_dec,     LD_pNN_HL_run},
    /*   00 100 011   */    {INC_SS_dec,        INC_SS_run},
    /*   00 100 100   */    {INC_R_dec,         INC_R_run},
    /*   00 100 101   */    {DEC_M_dec,         DEC_M_run},
    /*   00 100 110   */    {LD_R_N_dec,        LD_R_N_run},
    /*   00 100 111   */    {DAA_dec,           DAA_run},
    /*   00 101 000   */    {JR_Z_E_dec,        JR_Z_E_run},
    /*   00 101 001   */    {ADD_HL_SS_dec,     ADD_HL_SS_run},
    /*   00 101 010   */    {LD_HL_pNN_dec,     LD_HL_pNN_run},
    /*   00 101 011   */    {DEC_SS_dec,        DEC_SS_run},
    /*   00 101 100   */    {INC_R_dec,         INC_R_run},
    /*   00 101 101   */    {DEC_M_dec,         DEC_M_run},
    /*   00 101 110   */    {LD_R_N_dec,        LD_R_N_run},
    /*   00 101 111   */    {CPL_dec,           CPL_run},
    /*   00 110 000   */    {JR_NC_E_dec,       JR_NC_E_run},
    /*   00 110 001   */    {LD_DD_NN_dec,      LD_DD_NN_run},
    /*   00 110 010   */    {LD_pNN_A_dec,      LD_pNN_A_run},
    /*   00 110 011   */    {INC_SS_dec,        INC_SS_run},
    /*   00 110 100   */    {INC_pHL_dec,       INC_pHL_run},
    /*   00 110 101   */    {DEC_pHL_dec,       DEC_pHL_run},
    /*   00 110 110   */    {LD_pHL_N_dec,      LD_pHL_N_run},
    /*   00 110 111   */    {SCF_dec,           SCF_run},
    /*   00 111 000   */    {JR_C_E_dec,        JR_C_E_run},
    /*   00 111 001   */    {ADD_HL_SS_dec,     ADD_HL_SS_run},
    /*   00 111 010   */    {LD_A_pNN_dec,      LD_A_pNN_run},
    /*   00 111 011   */    {DEC_SS_dec,        DEC_SS_run},
    /*   00 111 100   */    {INC_R_dec,         INC_R_run},
    /*   00 111 101   */    {DEC_M_dec,         DEC_M_run},
    /*   00 111 110   */    {LD_R_N_dec,        LD_R_N_run},
    /*   00 111 111   */    {CCF_dec,           CCF_run},
    /*   01 000 000   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 000 001   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 000 010   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 000 011   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 000 100   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 000 101   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 000 110   */    {LD_R_pHL_dec,      LD_R_pHL_run},
    /*   01 000 111   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 001 000   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 001 001   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 001 010   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 001 011   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 001 100   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 001 101   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 001 110   */    {LD_R_pHL_dec,      LD_R_pHL_run},
    /*   01 001 111   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 010 000   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 010 001   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 010 010   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 010 011   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 010 100   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 010 101   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 010 110   */    {LD_R_pHL_dec,      LD_R_pHL_run},
    /*   01 010 111   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 011 000   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 011 001   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 011 010   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 011 011   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 011 100   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 011 101   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 011 110   */    {LD_R_pHL_dec,      LD_R_pHL_run},
    /*   01 011 111   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 100 000   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 100 001   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 100 010   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 100 011   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 100 100   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 100 101   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 100 110   */    {LD_R_pHL_dec,      LD_R_pHL_run},
    /*   01 100 111   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 101 000   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 101 001   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 101 010   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 101 011   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 101 100   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 101 101   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 101 110   */    {LD_R_pHL_dec,      LD_R_pHL_run},
    /*   01 101 111   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 110 000   */    {LD_pHL_R_dec,      LD_pHL_R_run},
    /*   01 110 001   */    {LD_pHL_R_dec,      LD_pHL_R_run},
    /*   01 110 010   */    {LD_pHL_R_dec,      LD_pHL_R_run},
    /*   01 110 011   */    {LD_pHL_R_dec,      LD_pHL_R_run},
    /*   01 110 100   */    {LD_pHL_R_dec,      LD_pHL_R_run},
    /*   01 110 101   */    {LD_pHL_R_dec,      LD_pHL_R_run},
    /*   01 110 110   */    {HALT, 0},
    /*   01 110 111   */    {LD_pHL_R_dec,      LD_pHL_R_run},
    /*   01 111 000   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 111 001   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 111 010   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 111 011   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 111 100   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 111 101   */    {LD_R_R_dec,        LD_R_R_run},
    /*   01 111 110   */    {LD_R_pHL_dec,      LD_R_pHL_run},
    /*   01 111 111   */    {LD_R_R_dec,        LD_R_R_run},
    /*   10 000 000   */    {ADD_A_R, 0},
    /*   10 000 001   */    {ADD_A_R, 0},
    /*   10 000 010   */    {ADD_A_R, 0},
    /*   10 000 011   */    {ADD_A_R, 0},
    /*   10 000 100   */    {ADD_A_R, 0},
    /*   10 000 101   */    {ADD_A_R, 0},
    /*   10 000 110   */    {ADD_A_pHL, 0},
    /*   10 000 111   */    {ADD_A_R, 0},
    /*   10 001 000   */    {ADC_A_S, 0},
    /*   10 001 001   */    {ADC_A_S, 0},
    /*   10 001 010   */    {ADC_A_S, 0},
    /*   10 001 011   */    {ADC_A_S, 0},
    /*   10 001 100   */    {ADC_A_S, 0},
    /*   10 001 101   */    {ADC_A_S, 0},
    /*   10 001 110   */    {ADC_A_pHL, 0},
    /*   10 001 111   */    {ADC_A_S, 0},
    /*   10 010 000   */    {SUB_S, 0},
    /*   10 010 001   */    {SUB_S, 0},
    /*   10 010 010   */    {SUB_S, 0},
    /*   10 010 011   */    {SUB_S, 0},
    /*   10 010 100   */    {SUB_S, 0},
    /*   10 010 101   */    {SUB_S, 0},
    /*   10 010 110   */    {SUB_pHL, 0},
    /*   10 010 111   */    {SUB_S, 0},
    /*   10 011 000   */    {SBC_A_S, 0},
    /*   10 011 001   */    {SBC_A_S, 0},
    /*   10 011 010   */    {SBC_A_S, 0},
    /*   10 011 011   */    {SBC_A_S, 0},
    /*   10 011 100   */    {SBC_A_S, 0},
    /*   10 011 101   */    {SBC_A_S, 0},
    /*   10 011 110   */    {SBC_A_pHL, 0},
    /*   10 011 111   */    {SBC_A_S, 0},
    /*   10 100 000   */    {AND_S, 0},
    /*   10 100 001   */    {AND_S, 0},
    /*   10 100 010   */    {AND_S, 0},
    /*   10 100 011   */    {AND_S, 0},
    /*   10 100 100   */    {AND_S, 0},
    /*   10 100 101   */    {AND_S, 0},
    /*   10 100 110   */    {AND_pHL, 0},
    /*   10 100 111   */    {AND_S, 0},
    /*   10 101 000   */    {XOR_S, 0},
    /*   10 101 001   */    {XOR_S, 0},
    /*   10 101 010   */    {XOR_S, 0},
    /*   10 101 011   */    {XOR_S, 0},
    /*   10 101 100   */    {XOR_S, 0},
    /*   10 101 101   */    {XOR_S, 0},
    /*   10 101 110   */    {XOR_pHL, 0},
    /*   10 101 111   */    {XOR_S, 0},
    /*   10 110 000   */    {OR_S, 0},
    /*   10 110 001   */    {OR_S, 0},
    /*   10 110 010   */    {OR_S, 0},
    /*   10 110 011   */    {OR_S, 0},
    /*   10 110 100   */    {OR_S, 0},
    /*   10 110 101   */    {OR_S, 0},
    /*   10 110 110   */    {OR_pHL, 0},
    /*   10 110 111   */    {OR_S, 0},
    /*   10 111 000   */    {CP_S, 0},
    /*   10 111 001   */    {CP_S, 0},
    /*   10 111 010   */    {CP_S, 0},
    /*   10 111 011   */    {CP_S, 0},
    /*   10 111 100   */    {CP_S, 0},
    /*   10 111 101   */    {CP_S, 0},
    /*   10 111 110   */    {CP_pHL, 0},
    /*   10 111 111   */    {CP_S, 0},
    /*   11 000 000   */    {RET_CC, 0},
    /*   11 000 001   */    {POP_QQ, 0},
    /*   11 000 010   */    {JP_CC_NN, 0},
    /*   11 000 011   */    {JP_NN, 0},
    /*   11 000 100   */    {CALL_CC_NN, 0},
    /*   11 000 101   */    {PUSH_QQ, 0},
    /*   11 000 110   */    {ADD_A_N, 0},
    /*   11 000 111   */    {RST_P, 0},
    /*   11 001 000   */    {RET_CC, 0},
    /*   11 001 001   */    {RET, 0},
    /*   11 001 010   */    {JP_CC_NN, 0},
    /*   11 001 011   */    {RunCommandWithPrefixCB, 0},
    /*   11 001 100   */    {CALL_CC_NN, 0},
    /*   11 001 101   */    {CALL_NN, 0},
    /*   11 001 110   */    {ADC_A_N, 0},
    /*   11 001 111   */    {RST_P, 0},
    /*   11 010 000   */    {RET_CC, 0},
    /*   11 010 001   */    {POP_QQ, 0},
    /*   11 010 010   */    {JP_CC_NN, 0},
    /*   11 010 011   */    {OUT_pN_A, 0},
    /*   11 010 100   */    {CALL_CC_NN, 0},
    /*   11 010 101   */    {PUSH_QQ, 0},
    /*   11 010 110   */    {SUB_N, 0},
    /*   11 010 111   */    {RST_P, 0},
    /*   11 011 000   */    {RET_CC, 0},
    /*   11 011 001   */    {EXX, 0},
    /*   11 011 010   */    {JP_CC_NN, 0},
    /*   11 011 011   */    {IN_A_pN, 0},
    /*   11 011 100   */    {CALL_CC_NN, 0},
    /*   11 011 101   */    {RunCommandWithPrefixDD, 0},
    /*   11 011 110   */    {SBC_A_N, 0},
    /*   11 011 111   */    {RST_P, 0},
    /*   11 100 000   */    {RET_CC, 0},
    /*   11 100 001   */    {POP_QQ, 0},
    /*   11 100 010   */    {JP_CC_NN, 0},
    /*   11 100 011   */    {EX_pSP_HL, 0},
    /*   11 100 100   */    {CALL_CC_NN, 0},
    /*   11 100 101   */    {PUSH_QQ, 0},
    /*   11 100 110   */    {AND_N, 0},
    /*   11 100 111   */    {RST_P, 0},
    /*   11 101 000   */    {RET_CC, 0},
    /*   11 101 001   */    {JP_pHL, 0},
    /*   11 101 010   */    {JP_CC_NN, 0},
    /*   11 101 011   */    {EX_DE_HL, 0},
    /*   11 101 100   */    {CALL_CC_NN, 0},
    /*   11 101 101   */    {RunCommandWithPrefixED, 0},
    /*   11 101 110   */    {XOR_N, 0},
    /*   11 101 111   */    {RST_P, 0},
    /*   11 110 000   */    {RET_CC, 0},
    /*   11 110 001   */    {POP_QQ, 0},
    /*   11 110 010   */    {JP_CC_NN, 0},
    /*   11 110 011   */    {DI, 0},
    /*   11 110 100   */    {CALL_CC_NN, 0},
    /*   11 110 101   */    {PUSH_QQ, 0},
    /*   11 110 110   */    {OR_N, 0},
    /*   11 110 111   */    {RST_P, 0},
    /*   11 111 000   */    {RET_CC, 0},
    /*   11 111 001   */    {LD_SP_HL, 0},
    /*   11 111 010   */    {JP_CC_NN, 0},
    /*   11 111 011   */    {EI, 0},
    /*   11 111 100   */    {CALL_CC_NN, 0},
    /*   11 111 101   */    {RunCommandWithPrefixFD, 0},
    /*   11 111 110   */    {CP_N, 0},
    /*   11 111 111   */    {RST_P, 0}
};
