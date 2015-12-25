#pragma once


int RunCommandWithPrefixED(void);

int LD_A_I(void);       // LD A, I      A <- I

int LD_A_R(void);       // LA A, R      À <- R

int LD_I_A(void);       // LD I, A      I <- A

int LD_R_A(void);       // LD R, A      R <- A

int LD_DD_pNN(void);    // LD DD, (NN)

int LD_pNN_DD(void);    // LD (NN), DD

int LDI(void);          // LDE          (DE) <- (HL)
                        //              DE   <- DE + 1
                        //              HL   <- HL + 1
                        //              BC   <- BC - 1

int LDIR(void);         // LDIR         (DE) <- (HL)
                        //              DE   <- DE + 1
                        //              HL   <- HL + 1
                        //              BC   <- BC - 1
                        //              while BC != 0

int LDD(void);          // LDD          (DE) <- (HL)
                        //              DE   <- DE - 1
                        //              HL   <- HL - 1
                        //              BC   <- BC - 1

int LDDR(void);         // LDDR         LDD
                        //              while BC != 0

int CPI(void);          // CPI          A ~ (HL)
                        //              HL <- HL + 1
                        //              BC <- BC - 1

int CPIR(void);         // CPIR         CPI
                        //              while BC != 0 && A != (HL)

int CPD(void);          // CPD          A ~ (HL)
                        //              HL <- HL - 1
                        //              BC <- BC - 1

int CPDR(void);         // CPDR         CPD
                        //              while BC != 0 && A != (HL)

int NEG(void);          // NEG          A <- 0 - A  (A <- (!A) + 1)

int IM0(void);          // IM 0

int IM1(void);          // IM 1

int IM2(void);          // IM 2

int ADC_HL_SS(void);    // ADC HL, SS

int SBC_HL_SS(void);    // SBC HL, SS

int RLD(void);          // RLD

int RRD(void);          // RRD

int RETN(void);         // RETN

int IN_R_pC(void);      // IN R, (C)    R <- (C)

int INI(void);          // INI          (HL) <- (C)
                        //              B    <- B - 1
                        //              HL   <- HL + 1

int INIR(void);         // INIR         INI
                        //              while B != 0

int IND(void);          // IND          (HL) <- (C)
                        //              B    <- B - 1
                        //              HL   <- HL - 1

int INDR(void);         // INDR         IND
                        //              while B != 0

int OUT_pC_R(void);     // OUT (C), R
