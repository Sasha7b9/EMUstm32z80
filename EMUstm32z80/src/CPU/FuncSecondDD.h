#pragma once


const pFuncIV secondLevelDD[256][2] =
{
    /*   00 000 000   */    {0, 0},
    /*   00 000 001   */    {0, 0},
    /*   00 000 010   */    {0, 0},
    /*   00 000 011   */    {0, 0},
    /*   00 000 100   */    {0, 0},
    /*   00 000 101   */    {0, 0},
    /*   00 000 110   */    {0, 0},
    /*   00 000 111   */    {0, 0},
    /*   00 001 000   */    {0, 0},
    /*   00 001 001   */    {ADD_IX_PP, 0},
    /*   00 001 010   */    {0, 0},
    /*   00 001 011   */    {0, 0},
    /*   00 001 100   */    {0, 0},
    /*   00 001 101   */    {0, 0},
    /*   00 001 110   */    {0, 0},
    /*   00 001 111   */    {0, 0},
    /*   00 010 000   */    {0, 0},
    /*   00 010 001   */    {0, 0},
    /*   00 010 010   */    {0, 0},
    /*   00 010 011   */    {0, 0},
    /*   00 010 100   */    {0, 0},
    /*   00 010 101   */    {0, 0},
    /*   00 010 110   */    {0, 0},
    /*   00 010 111   */    {0, 0},
    /*   00 011 000   */    {0, 0},
    /*   00 011 001   */    {ADD_IX_PP, 0},
    /*   00 011 010   */    {0, 0},
    /*   00 011 011   */    {0, 0},
    /*   00 011 100   */    {0, 0},
    /*   00 011 101   */    {0, 0},
    /*   00 011 110   */    {0, 0},
    /*   00 011 111   */    {0, 0},
    /*   00 100 000   */    {0, 0},
    /*   00 100 001   */    {LD_IX_NN, 0},
    /*   00 100 010   */    {LD_pNN_IX, 0},
    /*   00 100 011   */    {INC_IX_dec, INC_IX_run},
    /*   00 100 100   */    {0, 0},
    /*   00 100 101   */    {0, 0},
    /*   00 100 110   */    {0, 0},
    /*   00 100 111   */    {0, 0},
    /*   00 101 000   */    {0, 0},
    /*   00 101 001   */    {ADD_IX_PP, 0},
    /*   00 101 010   */    {LD_IX_pNN, 0},
    /*   00 101 011   */    {DEC_IX_dec, 0},
    /*   00 101 100   */    {0, 0},
    /*   00 101 101   */    {0, 0},
    /*   00 101 110   */    {0, 0},
    /*   00 101 111   */    {0, 0},
    /*   00 110 000   */    {0, 0},
    /*   00 110 001   */    {0, 0},
    /*   00 110 010   */    {0, 0},
    /*   00 110 011   */    {0, 0},
    /*   00 110 100   */    {INC_pIX_D, 0},
    /*   00 110 101   */    {0, 0},
    /*   00 110 110   */    {0, LD_pIX_D_N_run},
    /*   00 110 111   */    {0, 0},
    /*   00 111 000   */    {0, 0},
    /*   00 111 001   */    {ADD_IX_PP, 0},
    /*   00 111 010   */    {0, 0},
    /*   00 111 011   */    {0, 0},
    /*   00 111 100   */    {0, 0},
    /*   00 111 101   */    {0, 0},
    /*   00 111 110   */    {0, 0},
    /*   00 111 111   */    {0, 0},
    /*   01 000 000   */    {0, 0},
    /*   01 000 001   */    {0, 0},
    /*   01 000 010   */    {0, 0},
    /*   01 000 011   */    {0, 0},
    /*   01 000 100   */    {0, 0},
    /*   01 000 101   */    {0, 0},
    /*   01 000 110   */    {LD_R_pIX_D_dec, LD_R_pIX_D_run},
    /*   01 000 111   */    {0, 0},
    /*   01 001 000   */    {0, 0},
    /*   01 001 001   */    {ADD_IX_PP, 0},
    /*   01 001 010   */    {0, 0},
    /*   01 001 011   */    {0, 0},
    /*   01 001 100   */    {0, 0},
    /*   01 001 101   */    {0, 0},
    /*   01 001 110   */    {LD_R_pIX_D_dec, LD_R_pIX_D_run},
    /*   01 001 111   */    {0, 0},
    /*   01 010 000   */    {0, 0},
    /*   01 010 001   */    {0, 0},
    /*   01 010 010   */    {0, 0},
    /*   01 010 011   */    {0, 0},
    /*   01 010 100   */    {0, 0},
    /*   01 010 101   */    {0, 0},
    /*   01 010 110   */    {LD_R_pIX_D_dec, LD_R_pIX_D_run},
    /*   01 010 111   */    {0, 0},
    /*   01 011 000   */    {0, 0},
    /*   01 011 001   */    {ADD_IX_PP, 0},
    /*   01 011 010   */    {0, 0},
    /*   01 011 011   */    {0, 0},
    /*   01 011 100   */    {0, 0},
    /*   01 011 101   */    {0, 0},
    /*   01 011 110   */    {LD_R_pIX_D_dec, LD_R_pIX_D_run},
    /*   01 011 111   */    {0, 0},
    /*   01 100 000   */    {0, 0},
    /*   01 100 001   */    {0, 0},
    /*   01 100 010   */    {0, 0},
    /*   01 100 011   */    {0, 0},
    /*   01 100 100   */    {0, 0},
    /*   01 100 101   */    {0, 0},
    /*   01 100 110   */    {LD_R_pIX_D_dec, LD_R_pIX_D_run},
    /*   01 100 111   */    {0, 0},
    /*   01 101 000   */    {0, 0},
    /*   01 101 001   */    {ADD_IX_PP, 0},
    /*   01 101 010   */    {0, 0},
    /*   01 101 011   */    {0, 0},
    /*   01 101 100   */    {0, 0},
    /*   01 101 101   */    {0, 0},
    /*   01 101 110   */    {LD_R_pIX_D_dec, LD_R_pIX_D_run},
    /*   01 101 111   */    {0, 0},
    /*   01 110 000   */    {LD_pIX_D_R_dec, LD_pIX_D_R_run},
    /*   01 110 001   */    {LD_pIX_D_R_dec, LD_pIX_D_R_run},
    /*   01 110 010   */    {LD_pIX_D_R_dec, LD_pIX_D_R_run},
    /*   01 110 011   */    {LD_pIX_D_R_dec, LD_pIX_D_R_run},
    /*   01 110 100   */    {LD_pIX_D_R_dec, LD_pIX_D_R_run},
    /*   01 110 101   */    {LD_pIX_D_R_dec, LD_pIX_D_R_run},
    /*   01 110 110   */    {LD_R_pIX_D_dec, LD_R_pIX_D_run},
    /*   01 110 111   */    {LD_pIX_D_R_dec, LD_pIX_D_R_run},
    /*   01 111 000   */    {0, 0},
    /*   01 111 001   */    {ADD_IX_PP, 0},
    /*   01 111 010   */    {0, 0},
    /*   01 111 011   */    {0, 0},
    /*   01 111 100   */    {0, 0},
    /*   01 111 101   */    {0, 0},
    /*   01 111 110   */    {LD_R_pIX_D_dec, LD_R_pIX_D_run},
    /*   01 111 111   */    {0, 0},
    /*   10 000 000   */    {0, 0},
    /*   10 000 001   */    {0, 0},
    /*   10 000 010   */    {0, 0},
    /*   10 000 011   */    {0, 0},
    /*   10 000 100   */    {0, 0},
    /*   10 000 101   */    {0, 0},
    /*   10 000 110   */    {ADD_A_pIX_D, 0},
    /*   10 000 111   */    {0, 0},
    /*   10 001 000   */    {0, 0},
    /*   10 001 001   */    {0, 0},
    /*   10 001 010   */    {0, 0},
    /*   10 001 011   */    {0, 0},
    /*   10 001 100   */    {0, 0},
    /*   10 001 101   */    {0, 0},
    /*   10 001 110   */    {0, 0},
    /*   10 001 111   */    {0, 0},
    /*   10 010 000   */    {0, 0},
    /*   10 010 001   */    {0, 0},
    /*   10 010 010   */    {0, 0},
    /*   10 010 011   */    {0, 0},
    /*   10 010 100   */    {0, 0},
    /*   10 010 101   */    {0, 0},
    /*   10 010 110   */    {0, 0},
    /*   10 010 111   */    {0, 0},
    /*   10 011 000   */    {0, 0},
    /*   10 011 001   */    {0, 0},
    /*   10 011 010   */    {0, 0},
    /*   10 011 011   */    {0, 0},
    /*   10 011 100   */    {0, 0},
    /*   10 011 101   */    {0, 0},
    /*   10 011 110   */    {0, 0},
    /*   10 011 111   */    {0, 0},
    /*   10 100 000   */    {0, 0},
    /*   10 100 001   */    {0, 0},
    /*   10 100 010   */    {0, 0},
    /*   10 100 011   */    {0, 0},
    /*   10 100 100   */    {0, 0},
    /*   10 100 101   */    {0, 0},
    /*   10 100 110   */    {0, 0},
    /*   10 100 111   */    {0, 0},
    /*   10 101 000   */    {0, 0},
    /*   10 101 001   */    {0, 0},
    /*   10 101 010   */    {0, 0},
    /*   10 101 011   */    {0, 0},
    /*   10 101 100   */    {0, 0},
    /*   10 101 101   */    {0, 0},
    /*   10 101 110   */    {0, 0},
    /*   10 101 111   */    {0, 0},
    /*   10 110 000   */    {0, 0},
    /*   10 110 001   */    {0, 0},
    /*   10 110 010   */    {0, 0},
    /*   10 110 011   */    {0, 0},
    /*   10 110 100   */    {0, 0},
    /*   10 110 101   */    {0, 0},
    /*   10 110 110   */    {0, 0},
    /*   10 110 111   */    {0, 0},
    /*   10 111 000   */    {0, 0},
    /*   10 111 001   */    {0, 0},
    /*   10 111 010   */    {0, 0},
    /*   10 111 011   */    {0, 0},
    /*   10 111 100   */    {0, 0},
    /*   10 111 101   */    {0, 0},
    /*   10 111 110   */    {0, 0},
    /*   10 111 111   */    {0, 0},
    /*   11 000 000   */    {0, 0},
    /*   11 000 001   */    {0, 0},
    /*   11 000 010   */    {0, 0},
    /*   11 000 011   */    {0, 0},
    /*   11 000 100   */    {0, 0},
    /*   11 000 101   */    {0, 0},
    /*   11 000 110   */    {0, 0},
    /*   11 000 111   */    {0, 0},
    /*   11 001 000   */    {0, 0},
    /*   11 001 001   */    {0, 0},
    /*   11 001 010   */    {0, 0},
    /*   11 001 011   */    {RLC_pIX_D_and_BIT_B_pIX_D_and_SET_B_pIX_D_RES_B_pIX_D, 0},
    /*   11 001 100   */    {0, 0},
    /*   11 001 101   */    {0, 0},
    /*   11 001 110   */    {0, 0},
    /*   11 001 111   */    {0, 0},
    /*   11 010 000   */    {0, 0},
    /*   11 010 001   */    {0, 0},
    /*   11 010 010   */    {0, 0},
    /*   11 010 011   */    {0, 0},
    /*   11 010 100   */    {0, 0},
    /*   11 010 101   */    {0, 0},
    /*   11 010 110   */    {0, 0},
    /*   11 010 111   */    {0, 0},
    /*   11 011 000   */    {0, 0},
    /*   11 011 001   */    {0, 0},
    /*   11 011 010   */    {0, 0},
    /*   11 011 011   */    {0, 0},
    /*   11 011 100   */    {0, 0},
    /*   11 011 101   */    {0, 0},
    /*   11 011 110   */    {0, 0},
    /*   11 011 111   */    {0, 0},
    /*   11 100 000   */    {0, 0},
    /*   11 100 001   */    {POP_IX_dec, POP_IX_run},
    /*   11 100 010   */    {0, 0},
    /*   11 100 011   */    {EX_pSP_IX, 0},
    /*   11 100 100   */    {0, 0},
    /*   11 100 101   */    {PUSH_IX, 0},
    /*   11 100 110   */    {0, 0},
    /*   11 100 111   */    {0, 0},
    /*   11 101 000   */    {0, 0},
    /*   11 101 001   */    {JP_pIX, 0},
    /*   11 101 010   */    {0, 0},
    /*   11 101 011   */    {0, 0},
    /*   11 101 100   */    {0, 0},
    /*   11 101 101   */    {0, 0},
    /*   11 101 110   */    {0, 0},
    /*   11 101 111   */    {0, 0},
    /*   11 110 000   */    {0, 0},
    /*   11 110 001   */    {0, 0},
    /*   11 110 010   */    {0, 0},
    /*   11 110 011   */    {0, 0},
    /*   11 110 100   */    {0, 0},
    /*   11 110 101   */    {0, 0},
    /*   11 110 110   */    {0, 0},
    /*   11 110 111   */    {0, 0},
    /*   11 111 000   */    {0, 0},
    /*   11 111 001   */    {LD_SP_IX, 0},
    /*   11 111 010   */    {0, 0},
    /*   11 111 011   */    {0, 0},
    /*   11 111 100   */    {0, 0},
    /*   11 111 101   */    {0, 0},
    /*   11 111 110   */    {0, 0},
    /*   11 111 111   */    {0, 0}
};
