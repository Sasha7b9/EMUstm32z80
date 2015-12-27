#pragma once


#include "defines.h"


int RunCommand(void);

// First level
int LD_R_R(void);

int LD_R_N(void);

int LD_R_pHL(void);

int LD_pHL_R(void);

int LD_pHL_N(void);

int LD_A_pBC(void);

int LD_A_pDE(void);

int LD_A_pNN(void);

int LD_pBC_A(void);

int LD_pDE_A(void);

int LD_pNN_A(void);

int LD_DD_NN(void);

int LD_HL_pNN(void);

int LD_pNN_HL(void);

int LD_SP_HL(void);

int PUSH_QQ(void);

int POP_QQ(void);

int EX_DE_HL(void);

int EX_AF_AFalt(void);

int EXX(void);

int EX_pSP_HL(void);


int ADD_A_R(void);

int ADD_A_N(void);

int ADD_A_pHL(void);


int ADC_A_S(void);      // ADC A, S

int ADC_A_N(void);      // ADC A, N

int ADC_A_pHL(void);    // ADC A, (HL)


int SUB_S(void);        // SUB S        A <- A - S

int SUB_N(void);        // SUB N        A <- A - N

int SUB_pHL(void);      // SUB (HL)     A <- A - (HL)


int SBC_A_S(void);      // SBC A, S     A <- A - S - CF

int SBC_A_N(void);      // SBC A, N     A <- A - N - CF

int SBC_A_pHL(void);    // SBC A, (HL)  A <- A - (HL) - CF


int AND_S(void);        // AND S        A <- A & S

int AND_N(void);        // AND N        A <- A & N

int AND_pHL(void);      // AND (HL)     A <- A & (HL)


int OR_S(void);         // OR S         A <- A | S

int OR_N(void);         // OR N         A <- A | N

int OR_pHL(void);       // OR (HL)      A <- A | (HL)


int XOR_S(void);        // XOR S        A <- A ^ S

int XOR_N(void);        // XOR N        A <- A ^ N

int XOR_pHL(void);      // XOR (HL)     A <- A ^ (HL)


int CP_S(void);         // CP S         A == S

int CP_N(void);         // CP N         A == N

int CP_pHL(void);       // CP (HL)      A == (HL)


int INC_R(void);        // INC R        R <- R + 1

int INC_pHL(void);      // INC (HL)     (HL) <- (HL) + 1


int DEC_M(void);        // DEC M        M <- M - 1

int DEC_pHL(void);      // DEC (HL)     (HL) <- (HL) - 1


int CPL(void);          // CPL          A <- !A

int CCF(void);          // CCF          CF <- !CF

int SCF(void);          // CCF          CF <- 1

int NOP(void);          // NOP

int HALT(void);         // HALT

int DI(void);           // DI

int EI(void);           // EI


int ADD_HL_SS(void);    // ADD HL, SS   HL <- HL + SS

int INC_SS(void);       // INC SS       SS <- SS + 1

int DEC_SS(void);       // DEC SS       SS <- SS - 1


int RLCA(void);

int RLA(void);

int RRCA(void);

int RRA(void);


int JP_NN(void);        // JP NN        PC <- NN

int JP_CC_NN(void);     // JP CC, NN    jump for condition

int JR_E(void);         // JR E         PC <- PC + E

int JR_C_E(void);       // JR C, E      if (C == 1) PC <- PC + E

int JR_NC_E(void);      // JR NC, E     if (C == 0) PC <- PC + E

int JR_Z_E(void);       // JR Z, E      if (Z == 1) PC <- PC + E

int JR_NZ_E(void);      // JR NZ, E     if(Z == 0) PC <- PC + E

int JP_pHL(void);       // JP (HL)      PC <- HL

int DJNZ_E(void);       // DJNZ, E      B <- B - 1; if(B != 0) PC <- PC + E

int CALL_NN(void);      // CALL NN      (SP-1) <- PC[CT]
                        //              (SP-2) <- PC[LOW]
                        //              PC <- NN

int CALL_CC_NN(void);   // CALL CC, NN  if(CC)  CALL NN

int RET(void);          // RET          PC[LOW] <- (SP)
                        //              PC[HI] <- (SP + 1)

int RET_CC(void);       // RET CC       if(CC)  RET

int RST_P(void);        // RST P        (SP-1) <- PC[HI]
                        //              (SP-2) <- PC[LOW]
                        //              PC[HI] <- 0
                        //              PC[LOW] <- P

int IN_A_pN(void);      // IN A, (N)    A <- (N)

int OUT_pN_A(void);     // IN (N), A    (N) <- A
