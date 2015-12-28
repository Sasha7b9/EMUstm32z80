#pragma once


int RunCommandWithPrefixDD(void);

int LD_R_pIX_D(void);    // LD R, (IX + D)

int LD_pIX_D_R(void);    // LD (IX + D), R

int LD_pIX_D_N(void);    // LD (IY + D), N

int LD_IX_NN(void);     // LD IX, N

int LD_IX_pNN(void);    // LD IX, (NN)

int LD_pNN_IX(void);    // LD (NN), IX

int LD_SP_IX(void);     // LD SP, IX

int PUSH_IX(void);      // PUSH IX

int POP_IX(void);       // POP IX

int EX_pSP_IX(void);    // EX (SP), IX

int ADD_A_pIX_D(void);  // ADD A, (IX + D)

int INC_pIX_D(void);    // INC (IX + D)

int ADD_IX_PP(void);    // ADD IX, PP

int INC_IX(void);       // INC IX

int DEC_IX(void);       // DEC IX

int RLC_pIX_D_and_BIT_B_pIX_D_and_SET_B_pIX_D_RES_B_pIX_D(void);    // RLC (IX + D) and BIT B, (IX + D) and SET B, (IX + D)

int JP_pIX(void);       // JP (IX)

int ADD_IX_PP(void);
