#include "instr.h"
#include "registers.h"
#include "RAM.h"
#include "DAA.h"
#include "Hardware/ports.h"
#include "instrCB.h"
#include "instrDD.h"
#include "instrED.h"
#include "instrFD.h"
#include "common.h"


#include <string.h>
#include <stdio.h>


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LD_R_R(void)
{
#ifdef LISTING

    AddAddress(PC);
    *tackts = 4;

    sprintf(mnemonic, "LD %s,%s", R8_HI_Name(prevPC), R8_LO_Name(prevPC));
    sprintf(transcript, "%s<-%s", R8_HI_Name(prevPC), R8_LO_Name(prevPC));

    return -1;

#else

    R8_HI(prevPC) = R8_LO(prevPC);

    return 4;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_R_N(void)
{
#ifdef LISTING

    AddAddress(PC + 1);
    AddOpcode(RAM8(PC));
    *tackts = 7;

    uint8 valR = prevPC;
    uint8 N = PCandInc();

    sprintf(mnemonic, "LD %s,%02X", R8_HI_Name(valR), N);

    return -1;

#else

    R8_HI(prevPC) = PCandInc();

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_R_pHL(void)
{
#ifdef LISTING

    *tackts = 7;
    AddAddress(PC);

    sprintf(mnemonic, "LD %s,[HL]", R8_HI_Name(prevPC));
    sprintf(transcript, "%s<-[HL]", R8_HI_Name(prevPC));

    return -1;

#else

    R8_HI(prevPC) = pHL;

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_pHL_R(void)
{
#ifdef LISTING

    AddAddress(PC);
    sprintf(mnemonic, "LD [HL],%s", R8_LO_Name(prevPC));
    return -1;

#else

    pHL = R8_LO(prevPC);

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_pHL_N(void)
{
#ifdef LISTING

    *tackts = 10;
    AddOpcode(RAM8(PC));
    AddAddress(PC + 1);
    uint8 value = PCandInc();

    sprintf(mnemonic, "LD (HL),%2x", value);
    sprintf(transcript, "(HL)<-%2x", value);

    return -1;

#else

    pHL = PCandInc();

    return 10;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_A_pBC(void)
{
#ifdef LISTING

    AddAddress(PC);
    sprintf(mnemonic, "LD A,[BC]");
    return -1;

#else

    A = RAM[BC];

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_A_pDE(void)
{
#ifdef LISTING

    AddAddress(PC);
    sprintf(mnemonic, "LD A,[DE]");
    return -1;

#else

    A = RAM[DE];

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_A_pNN(void)
{
#ifdef LISTING

    AddOpcode(RAM8(PC));
    AddOpcode(RAM8(PC + 1));
    AddAddress(PC + 2);

    sprintf(mnemonic, "LD A,[%04X]", PC16andInc());

    return -1;

#else

    A = RAM[PC16andInc()];

    return 13;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_pBC_A(void)
{
#ifdef LISTING

    AddAddress(PC);
    sprintf(mnemonic, "LD [BC],A");
    return -1;

#else

    RAM[BC] = A;

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_pDE_A(void)
{
#ifdef LISTING

    AddAddress(PC);
    sprintf(mnemonic, "LD [DE],A");
    return -1;

#else

    RAM[DE] = A;

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_pNN_A(void)
{
#ifdef LISTING

    AddOpcode(RAM8(PC));
    AddOpcode(RAM8(PC + 1));
    sprintf(mnemonic, "LD (%04x),A", PC16andInc());
    AddAddress(PC);
    return -1;

#else

    RAM[PC16andInc()] = A;

    return 13;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_DD_NN(void)
{
#ifdef LISTING

    uint8 valDD = prevPC;
    AddOpcode(RAM8(PC));
    AddOpcode(RAM8(PC + 1));
    AddAddress(PC + 2);
    uint16 NN = PC16andInc();

    sprintf(mnemonic, "LD %s,%04X", DD_45_Name(valDD), NN);

    return -1;

#else

    DD_45(prevPC) = PC16andInc();

    return 10;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_pNN_HL(void)
{
#ifdef LISTING

    *tackts = 16;
    
    AddOpcode(RAM8(PC));
    AddOpcode(RAM8(PC + 1));

    uint16 NN = PC16andInc();
    AddAddress(PC);

    sprintf(mnemonic, "LD [%04X],HL", NN);
    sprintf(transcript, "[%04X]<-HL", NN);

    return -1;

#else

    uint16 address = PC16andInc();

    RAM[address] = L;
    RAM[address + 1] = H;

    return 16;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_SP_HL(void)
{
#ifdef LISTING

    AddAddress(PC);
    strcpy(mnemonic, "LD SP,HL");
    return -1;

#else

    SP = HL;

    return 6;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int PUSH_QQ(void)
{
#ifdef LISTING

    *tackts = 11;
    AddAddress(PC);

    sprintf(mnemonic, "PUSH %s", QQ_45_Name(prevPC));
    sprintf(transcript, "(SP-2)<-%s, SP<-SP-2", QQ_45_Name(prevPC));

    return -1;

#else

    RAM[SP - 2] = (uint8)QQ_45(prevPC);
    RAM[SP - 1] = (uint8)(QQ_45(prevPC) >> 8);
    SP -= 2;

    return 11;
#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int POP_QQ(void)
{
#ifdef LISTING

    AddAddress(PC);

    sprintf(mnemonic, "POP %s", QQ_45_Name(prevPC));

    return -1;

#else

    QQ_45(prevPC) = RAM[SP] + RAM[SP + 1] * 256;
    SP += 2;

    return 10;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int EX_DE_HL(void)
{
#ifdef LISTING

    AddAddress(PC);
    strcpy(mnemonic, "EX DE,HL");
    return -1;

#else

    uint16 temp;

    EXCH(DE, HL);

    return 4;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int EX_AF_AFalt(void)
{
#ifdef LISTING

    AddAddress(PC);
    strcpy(mnemonic, "EX AF,AF\'");
    return -1;

#else

    uint8 temp;

    EXCH(A, Aalt);
    EXCH(F, RFalt);

    return 4;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int EXX(void)
{
#ifdef LISTING

    *tackts = 4;
    AddAddress(PC);
    strcpy(mnemonic, "EXX");
    strcpy(transcript, "BC<->BC', DE<->DE', HL<->HL'");

    return -1;

#else

    uint8 temp;

    EXCH(B, Balt);
    EXCH(C, RCalt);
    EXCH(D, RDalt);
    EXCH(E, REalt);
    EXCH(H, RHalt);
    EXCH(L, RLalt);

    return 4;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int EX_pSP_HL(void)
{
#ifdef LISTING

    AddAddress(PC);
    sprintf(mnemonic, "EX [SP],HL");
    return -1;

#else

    uint8 temp;

    EXCH(H, RAM[SP + 1]);
    EXCH(L, RAM[SP]);

    return 9;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int ADD_A_R(void)
{
#ifdef LISTING

    AddAddress(PC);
    sprintf(mnemonic, "LD A,%s", R8_LO_Name(prevPC));
    return -1;

#else

    A += R8_LO(prevPC);

    return 4;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int ADD_A_N(void)
{
#ifdef LISTING

    AddOpcode(RAM8(PC));
    AddAddress(PC + 1);
    sprintf(mnemonic, "ADD A,0x%02x", PCandInc());
    return -1;

#else

    A += PCandInc();

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int ADD_A_pHL(void)
{
#ifdef LISTING

    AddAddress(PC);
    sprintf(mnemonic, "ADD A,[HL]");
    return -1;

#else

    A += pHL;

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int ADC_A_S(void)
{
#ifdef LISTING

    AddAddress(PC + 1);
    AddOpcode(RAM8(PC));
    sprintf(mnemonic, "ADC A,%s", R8_LO_Name(prevPC));
    return -1;

#else

    A += R8_LO(prevPC) + CF;

    return 4;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int ADC_A_N(void)
{
#ifdef LISTING

    AddAddress(PC + 1);
    AddOpcode(RAM8(PC));
    sprintf(mnemonic, "ADC A,%02X", PCandInc());
    return -1;

#else

    A += PCandInc() + CF;

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int ADC_A_pHL(void)
{
    A += pHL + CF;

    return 7;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int SUB_S(void)
{
#ifdef LISTING

    AddAddress(PC);
    sprintf(mnemonic, "SUB %s", R8_LO_Name(prevPC));
    return -1;

#else

    A -= R8_LO(prevPC);

    return 4;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int SUB_N(void)
{
#ifdef LISTING

    AddAddress(PC + 1);
    AddOpcode(RAM8(PC));
    sprintf(mnemonic, "SUB %02X", PCandInc());
    return -1;

#else

    A -= PCandInc();

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int SUB_pHL(void)
{
    A -= pHL;

    return 7;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_HL_pNN(void)
{
#ifdef LISTING

    AddOpcode(RAM8(PC));
    AddOpcode(RAM8(PC + 1));
    uint16 address = PC16andInc();
    AddAddress(PC);
    *tackts = 16;

    sprintf(mnemonic, "LD HL,[%04X]", address);
    sprintf(transcript, "HL<-[%04X]", address);

    return -1;

#else
    HL = PC16andInc();

    return 16;
#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int SBC_A_S(void)
{
#ifdef LISTING

    AddAddress(PC);
    sprintf(mnemonic, "SBC A,%s", R8_LO_Name(prevPC));
    return -1;

#else

    A -= R8_LO(prevPC) - CF;

    return 4;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int SBC_A_N(void)
{
#ifdef LISTING

    AddOpcode(RAM8(PC));
    AddAddress(PC + 1);
    sprintf(mnemonic, "SBC A,%02X", PCandInc());
    return -1;

#else

    A -= PCandInc() - CF;

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int SBC_A_pHL(void)
{
#ifdef LISTING

    AddAddress(PC);
    sprintf(mnemonic, "SBC A,[HL]");
    return -1;

#else

    A -= pHL - CF;

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int AND_S(void)
{
#ifdef LISTING

    *tackts = 4;
    AddAddress(PC);

    sprintf(mnemonic, "AND %s", R8_LO_Name(prevPC));
    sprintf(transcript, "A<-A&%s", R8_LO_Name(prevPC));
    strcpy(flags, "++X1XP00");

    return -1;

#else

    A &= R8_LO(prevPC);

    return 4;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int AND_N(void)
{
#ifdef LISTING

    AddOpcode(RAM8(PC));
    AddAddress(PC + 1);
    sprintf(mnemonic, "AND %02X", PCandInc());
    return -1;

#else

    A &= PCandInc();

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int AND_pHL(void)
{
#ifdef LISTING

    AddAddress(PC);
    strcpy(mnemonic, "AND [HL]");
    return -1;

#else

    A &= pHL;

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int OR_S(void)
{
#ifdef LISTING

    AddAddress(PC);

    sprintf(mnemonic, "OR %s", R8_LO_Name(prevPC));

    return -1;

#else

    A |= R8_LO(prevPC);

    return 4;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int OR_N(void)
{
#ifdef LISTING

    AddOpcode(RAM8(PC));
    AddAddress(PC + 1);
    sprintf(mnemonic, "OR %02X", PCandInc());
    return -1;

#else

    A |= PCandInc();

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int OR_pHL(void)
{
#ifdef LISTING

    AddAddress(PC);
    strcpy(mnemonic, "OR [HL]");
    return -1;

#else

    A |= pHL;

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int XOR_S(void)
{
#ifdef LISTING

    sprintf(mnemonic, "XOR %s", R8_LO_Name(prevPC));
    sprintf(transcript, "A<-A(+)%s", R8_LO_Name(prevPC));
    strcpy(flags, "++X0XP00");
    *tackts = 4;
    AddAddress(PC);
    return -1;

#else

    A ^= R8_LO(prevPC);
    return 4;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int XOR_N(void)
{
#ifdef LISTING

    AddOpcode(RAM8(PC));
    AddAddress(PC + 1);
    sprintf(mnemonic, "XOR %02X", PCandInc());
    return -1;

#else

    A ^= PCandInc();

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int XOR_pHL(void)
{
#ifdef LISTING

    AddAddress(PC);
    strcpy(mnemonic, "XOR [HL]");
    return -1;

#else

    A ^= pHL;

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int CP_S(void)
{
#ifdef LISTING

    AddAddress(PC);
    *tackts = 4;

    strcpy(flags, "++X+XV1+");
    sprintf(mnemonic, "CP %s", R8_LO_Name(prevPC));
    sprintf(transcript, "A ~ %s", R8_LO_Name(prevPC));
    sprintf(comment, "compare");

    return -1;

#else

    uint8 value = R8_LO(prevPC);

    SET_N;

    if(A == value)
    {
        SET_Z;
    }
    else
    {
        RES_Z;
    }

    if(A < value)
    {
        SET_C;
        SET_S;
    }
    else
    {
        RES_C;
        RES_S;
    }

    if((value & 0x0f) > (A & 0x0f))
    {
        SET_H;
    }
    else
    {
        RES_H;
    }

    return 4;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int CP_N(void)
{
#ifdef LISTING

    AddOpcode(RAM8(PC));
    AddAddress(PC + 1);

    sprintf(mnemonic, "CP %02X", PCandInc());
    
    return -1;

#else

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int CP_pHL(void)
{
#ifdef LISTING

    AddAddress(PC);
    strcpy(mnemonic, "CP [HL]");
    return -1;

#else

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int INC_R(void)
{
#ifdef LISTING

    AddAddress(PC);
    sprintf(mnemonic, "INC %s", R8_HI_Name(prevPC));
    return -1;

#else

    R8_HI(prevPC) += 1;

    // + + x + x v 0 .

    RES_N;

    /*
    */

    return 4;

#endif
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
int INC_pHL(void)
{
#ifdef LISTING

    AddAddress(PC);
    strcpy(mnemonic, "INC [HL]");
    return -1;

#else

    pHL += 1;

    // + + x + x v 0 .

    RES_N;

    /*
    */

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int DEC_M(void)
{
#ifdef LISTING

    AddAddress(PC);
    sprintf(mnemonic, "DEC %s", R8_HI_Name(prevPC));
    return -1;

#else

    R8_HI(prevPC) -= 1;

    // + + x + x v 1 .

    SET_N;

    /*
    */

    return 4;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int DEC_pHL(void)
{
#ifdef LISTING

    *tackts = 11;
    AddAddress(PC);

    strcpy(mnemonic, "DEC (HL)");
    strcpy(transcript, "(HL)<-(HL)+1");
    strcpy(flags, "++X+XV0.");

    return -1;

#else

    pHL += 1;

    // + + x + x v 1 .

    SET_N;

    /**/

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int CPL(void)
{
#ifdef LISTING

    AddAddress(PC);
    sprintf(mnemonic, "CPL");
    return -1;

#else

    A = ~A;

    // . . x + x . 1 .

    // H WARN

    SET_N;

    return 4;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int CCF(void)
{
#ifdef LISTING

    AddAddress(PC);
    strcpy(mnemonic, "CCF");
    return -1;

#else

    if(CF)
    {
        RES_C;
    }
    else
    {
        SET_C;
    }

    // . . x x x . 0 +

    RES_N;

    return 4;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int SCF(void)
{
#ifdef LISTING

    AddAddress(PC);
    sprintf(mnemonic, "SCF");
    return -1;

#else

    SET_C;

    // . . x 0 x . 0 +

    RES_H;
    RES_N;

    return 4;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int NOP(void)
{
#ifdef LISTING

    AddAddress(PC);
    *tackts = 4;

    strcpy(mnemonic, "NOP");

    return -1;

#else

    return 4;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int HALT(void)
{
#ifdef LISTING

    AddAddress(PC);
    strcpy(mnemonic, "HALT");
    return -1;

#else

    return 0;   // WARN There halt CPU

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int DI(void)
{
#ifdef LISTING

    strcpy(mnemonic, "DI");
    strcpy(transcript, "IFF1<-0, IFF2<-0");
    strcpy(comment, "reset the maskable interrupt");
    *tackts = 4;

    AddAddress(PC);

    return -1;

#else
    IFF1 = 0;
    IFF2 = 0;

    return 4;
#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int EI(void)
{
#ifdef LISTING

    AddAddress(PC);
    strcpy(mnemonic, "EI");
    return -1;

#else

    IFF1 = 1;
    IFF2 = 1;

    return 4;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int ADD_HL_SS(void)
{
#ifdef LISTING

    AddAddress(PC);
    *tackts = 11;
    sprintf(mnemonic, "ADD HL,%s", SS_45_Name(prevPC));
    sprintf(transcript, "HL<-HL+%s", SS_45_Name(prevPC));
    strcat(flags, "++XXXV0+");
    return -1;

#else

    HL += SS_45(prevPC);

    // . . x x x . 0 +

    RES_N;

    // C WARN

    return 11;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int INC_SS(void)
{
#ifdef LISTING

    *tackts = 6;
    AddAddress(PC);
    sprintf(mnemonic, "INC %s", SS_45_Name(prevPC));
    sprintf(transcript, "%s<-%s+1", SS_45_Name(prevPC), SS_45_Name(prevPC));
    return -1;

#else

    SS_45(prevPC) += 1;

    return 6;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int DEC_SS(void)
{
#ifdef LISTING

    *tackts = 6;
    AddAddress(PC);

    sprintf(mnemonic, "DEC %s", SS_45_Name(prevPC));
    sprintf(transcript, "%s<-%s-1", SS_45_Name(prevPC), SS_45_Name(prevPC));

    return -1;

#else

    SS_45(prevPC) -= 1;

    return 6;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RLCA(void)
{
#ifdef LISTING

    AddAddress(PC);
    strcpy(mnemonic, "RLCA");
    return -1;

#else

    uint8 hiBit = GET_BIT(A, 7);

    A <<= 1;

    LOAD_BIT(A, 0, hiBit);
    LOAD_C(hiBit);

    // . . x 0 x . 0 +
    RES_H;
    RES_N;

    return 4;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RLA(void)
{
#ifdef LISTING

    AddAddress(PC);
    sprintf(mnemonic, "RLA");
    return -1;

#else

    uint8 hiBit = GET_BIT(A, 7);
    uint8 oldCY = CF;

    A <<= 1;
    LOAD_C(hiBit);
    LOAD_BIT(A, 0, oldCY);

    // . . x 0 x . 0 +
    RES_H;
    RES_N;

    return 4;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RRCA(void)
{
#ifdef LISTING

    AddAddress(PC);
    strcpy(mnemonic, "RRCA");
    return -1;

#else

    uint8 loBit = GET_BIT(A, 0);

    A >>= 1;
    LOAD_BIT(A, 7, loBit);
    LOAD_C(loBit);

    // . . x 0 x . 0 +
    RES_H;
    RES_N;

    return 4;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RRA(void)
{
#ifdef LISTING

    AddAddress(PC);
    strcpy(mnemonic, "RRA");
    return -1;

#else

    uint8 loBit = GET_BIT(A, 0);
    uint8 oldCY = CF;

    A >>= 1;
    LOAD_BIT(A, 7, oldCY);
    LOAD_C(loBit);

    // . . x 0 x . 0 +
    RES_H;
    RES_N;

    return 4;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int JP_NN(void)
{
#ifdef LISTING

    AddOpcode(RAM8(PC));
    AddOpcode(RAM8(PC + 1));

    uint16 address = PC16andInc();

    AddAddress(address);

    sprintf(mnemonic, "JP %04X", address);
    sprintf(transcript, "PC<-%04X", address);

    *tackts = 10;

    return -1;

#else

    PC = PC16andInc();

    return 10;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static bool Cond_NZ(void)
{
    return (ZF == 0);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static bool Cond_Z(void)
{
    return (ZF == 1);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static bool Cond_NC(void)
{
    return (CF == 0);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static bool Cond_C(void)
{
    return (CF == 1);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static bool Cond_PO(void)
{
    return (PF == 0);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static bool Cond_PE(void)
{
    return (PF == 1);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static bool Cond_P(void)
{
    return (SF == 0);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static bool Cond_M(void)
{
    return (SF == 1);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static char* Cond_Name(uint8 value)
{
    const char* names[8] =
    {
        "NZ",
        "Z",
        "NC",
        "C",
        "PO",
        "PE",
        "P",
        "M"
    };

    return (char*)names[CC(value)];
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static bool Cond(uint8 value)
{
    const pFuncBV funcs[8] =
    {
        Cond_NZ,
        Cond_Z,
        Cond_NC,
        Cond_C,
        Cond_PO,
        Cond_PE,
        Cond_P,
        Cond_M
    };

    uint8 cond = CC(value);

    return funcs[cond]();
}



//------------------------------------------------------------------------------------------------------------------------------------------------------
int JP_CC_NN(void)
{
#ifdef LISTING

    char *nameCC = Cond_Name(prevPC);

    AddOpcode(RAM8(PC));
    AddOpcode(RAM8(PC + 1));

    uint16 NN = PC16andInc();

    sprintf(mnemonic, "JP %s,%04x", nameCC, NN);

    AddAddress(PC);
    AddAddress(NN);

    return -1;

#else

    bool cond = Cond(prevPC);

    uint16 address = PC16andInc();

    if(cond)
    {
        PC = address;
    }

    return 10;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static void WriteE(char *name)
{
    AddOpcode(RAM8(PC));
    if(name[0])     // For JR E not write address
    {
        AddAddress(PC + 1);
    }

    uint8 value = PCandInc();

    int shift = ((int)((int8)value)) + 2;
    uint newAddress = PC + shift - 2;

    sprintf(mnemonic, "JR %s%dd (%04X)", name, shift, newAddress);

    AddAddress(newAddress);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int DJNZ_E(void)
{
#ifdef LISTING

    AddOpcode(RAM8(PC));
    AddAddress(PC + 1);
    uint8 value = PCandInc();
    int shift = ((int)((int8)value)) + 2;
    uint newAddress = PC + shift - 2;
    sprintf(mnemonic, "DJNZ %dd (%04X)", shift, newAddress);
    AddAddress(newAddress);
    return -1;

#else

    B -= 1;

    uint8 delta = PCandInc();

    if (B)
    {
        AddPC(delta);
        return 13;
    }

    return 8;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int JR_NZ_E(void)
{
#ifdef LISTING
   
    WriteE("NZ,");

    return -1;

#else

    uint8 address = PCandInc();
    if(ZF == 0)
    {
        AddPC(address);
        return 12;
    }
    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int JR_E(void)
{
#ifdef LISTING

    WriteE("");

    return -1;

#else

    AddPC(PCandInc());

    return 12;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int JR_Z_E(void)
{
#ifdef LISTING

    WriteE("Z,");

    return -1;

#else

    uint8 address = PCandInc();
    if(ZF)
    {
        AddPC(address);
        return 12;
    }

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int JR_NC_E(void)
{
#ifdef LISTING

    WriteE("NC,");

    return -1;

#else

    uint8 address = PCandInc();
    if(CF == 0)
    {
        AddPC(address);
        return 12;
    }

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int JR_C_E(void)
{
#ifdef LISTING

    WriteE("C,");

    return -1;

#else

    uint8 address = PCandInc();
    if(CF)
    {
        AddPC(address);
        return 12;
    }

    return 7;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int JP_pHL(void)
{
#ifdef LISTING

    strcpy(mnemonic, "JP [HL]");
    return -1;

#else

    PC = HL;
    return 4;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int CALL_NN(void)
{
#ifdef LISTING

    *tackts = 17;
    AddOpcode(RAM8(PC));
    AddOpcode(RAM8(PC + 1));

    uint16 NN = PC16andInc();
    AddAddress(NN);
    AddAddress(PC);

    sprintf(mnemonic, "CALL %04X", NN);
    sprintf(transcript, "(SP-2)<-PC, PC<-%04X", NN);

    return -1;

#else

    uint16 valuePC = ValuePC();

    RAM[SP - 1] = (uint8)(valuePC >> 8);
    RAM[SP - 2] = (uint8)(valuePC);
    PC = PC16andInc();

    return 17;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int CALL_CC_NN(void)
{
#ifdef LISTING

    AddOpcode(RAM8(PC));
    AddOpcode(RAM8(PC + 1));
    AddAddress(PC + 2);
    uint8 value = prevPC;
    uint16 newAddress = PC16andInc();
    AddAddress(newAddress);
    sprintf(mnemonic, "CALL %s,%04X", Cond_Name(value), newAddress);
    return -1;

#else

    if(Cond(prevPC))
    {
        return CALL_NN();
    }

    PC16andInc();
    return 10;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RET(void)
{
#ifdef LISTING

    strcpy(mnemonic, "RET");
    return -1;

#else

    PC = RAM16(SP);
    return 10;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RET_CC(void)
{
#ifdef LISTING

    AddAddress(PC);

    sprintf(mnemonic, "RET %s", Cond_Name(prevPC));

    return -1;

#else

    if(Cond(prevPC))
    {
        RET();
        return 11;
    }
    return 5;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RST_P(void)
{
    const uint8 P[8] =
    {
        0x00,
        0x08,
        0x10,
        0x18,
        0x20,
        0x28,
        0x30,
        0x38
    };

#ifdef LISTING

    AddAddress(PC);
    int address = P[(prevPC >> 3) & 7];
    AddAddress(address);
    sprintf(mnemonic, "RST %02X", address);

    return -1;

#else
   
    uint8 T = (prevPC >> 3) & 7;

    uint16 valuePC = ValuePC();

    RAM[SP - 1] = (uint8)(valuePC >> 8);
    RAM[SP - 2] = (uint8)valuePC;

    PC = P[T];

    return 11;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int IN_A_pN(void)
{
#ifdef LISTING

    AddOpcode(RAM8(PC));
    AddAddress(PC + 1);
    sprintf(mnemonic, "IN A,(%02X)", PCandInc());
    return -1;

#else

    A = ReadPort(PCandInc());
    return 11;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int OUT_pN_A(void)
{
#ifdef LISTING

    *tackts = 11;
    AddAddress(PC + 1);
    AddOpcode(RAM8(PC));
    uint8 N = PCandInc();

    sprintf(mnemonic, "OUT (%02x), A", N);
    sprintf(transcript, "(%02x) <- A", N);
    sprintf(comment, "N - A0...A7, A - A8...A15");

    return -1;

#else

    WritePort(PCandInc(), A);
    return 11;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RunCommand(void)
{
    const pFuncIV firstLevel[256] =
    {
        /*   00 000 000   */ NOP,
        /*   00 000 001   */ LD_DD_NN,
        /*   00 000 010   */ LD_pBC_A,
        /*   00 000 011   */ INC_SS,
        /*   00 000 100   */ INC_R,
        /*   00 000 101   */ DEC_M,
        /*   00 000 110   */ LD_R_N,
        /*   00 000 111   */ RLCA,
        /*   00 001 000   */ EX_AF_AFalt,
        /*   00 001 001   */ ADD_HL_SS,
        /*   00 001 010   */ LD_A_pBC,
        /*   00 001 011   */ DEC_SS,
        /*   00 001 100   */ INC_R,
        /*   00 001 101   */ DEC_M,
        /*   00 001 110   */ LD_R_N,
        /*   00 001 111   */ RRCA,
        /*   00 010 000   */ DJNZ_E,
        /*   00 010 001   */ LD_DD_NN,
        /*   00 010 010   */ LD_pDE_A,
        /*   00 010 011   */ INC_SS,
        /*   00 010 100   */ INC_R,
        /*   00 010 101   */ DEC_M,
        /*   00 010 110   */ LD_R_N,
        /*   00 010 111   */ RLA,
        /*   00 011 000   */ JR_E,
        /*   00 011 001   */ ADD_HL_SS,
        /*   00 011 010   */ LD_A_pDE,
        /*   00 011 011   */ DEC_SS,
        /*   00 011 100   */ INC_R,
        /*   00 011 101   */ DEC_M,
        /*   00 011 110   */ LD_R_N,
        /*   00 011 111   */ RRA,
        /*   00 100 000   */ JR_NZ_E,
        /*   00 100 001   */ LD_DD_NN,
        /*   00 100 010   */ LD_pNN_HL,
        /*   00 100 011   */ INC_SS,
        /*   00 100 100   */ INC_R,
        /*   00 100 101   */ DEC_M,
        /*   00 100 110   */ LD_R_N,
        /*   00 100 111   */ DAA,
        /*   00 101 000   */ JR_Z_E,
        /*   00 101 001   */ ADD_HL_SS,
        /*   00 101 010   */ LD_HL_pNN,
        /*   00 101 011   */ DEC_SS,
        /*   00 101 100   */ INC_R,
        /*   00 101 101   */ DEC_M,
        /*   00 101 110   */ LD_R_N,
        /*   00 101 111   */ CPL,
        /*   00 110 000   */ JR_NC_E,
        /*   00 110 001   */ LD_DD_NN,
        /*   00 110 010   */ LD_pNN_A,
        /*   00 110 011   */ INC_SS,
        /*   00 110 100   */ INC_pHL,
        /*   00 110 101   */ DEC_pHL,
        /*   00 110 110   */ LD_pHL_N,
        /*   00 110 111   */ SCF,
        /*   00 111 000   */ JR_C_E,
        /*   00 111 001   */ ADD_HL_SS,
        /*   00 111 010   */ LD_A_pNN,
        /*   00 111 011   */ DEC_SS,
        /*   00 111 100   */ INC_R,
        /*   00 111 101   */ DEC_M,
        /*   00 111 110   */ LD_R_N,
        /*   00 111 111   */ CCF,

        /*   01 000 000   */ LD_R_R,
        /*   01 000 001   */ LD_R_R,
        /*   01 000 010   */ LD_R_R,
        /*   01 000 011   */ LD_R_R,
        /*   01 000 100   */ LD_R_R,
        /*   01 000 101   */ LD_R_R,
        /*   01 000 110   */ LD_R_pHL,
        /*   01 000 111   */ LD_R_R,
        /*   01 001 000   */ LD_R_R,
        /*   01 001 001   */ LD_R_R,
        /*   01 001 010   */ LD_R_R,
        /*   01 001 011   */ LD_R_R,
        /*   01 001 100   */ LD_R_R,
        /*   01 001 101   */ LD_R_R,
        /*   01 001 110   */ LD_R_pHL,
        /*   01 001 111   */ LD_R_R,
        /*   01 010 000   */ LD_R_R,
        /*   01 010 001   */ LD_R_R,
        /*   01 010 010   */ LD_R_R,
        /*   01 010 011   */ LD_R_R,
        /*   01 010 100   */ LD_R_R,
        /*   01 010 101   */ LD_R_R,
        /*   01 010 110   */ LD_R_pHL,
        /*   01 010 111   */ LD_R_R,
        /*   01 011 000   */ LD_R_R,
        /*   01 011 001   */ LD_R_R,
        /*   01 011 010   */ LD_R_R,
        /*   01 011 011   */ LD_R_R,
        /*   01 011 100   */ LD_R_R,
        /*   01 011 101   */ LD_R_R,
        /*   01 011 110   */ LD_R_pHL,
        /*   01 011 111   */ LD_R_R,
        /*   01 100 000   */ LD_R_R,
        /*   01 100 001   */ LD_R_R,
        /*   01 100 010   */ LD_R_R,
        /*   01 100 011   */ LD_R_R,
        /*   01 100 100   */ LD_R_R,
        /*   01 100 101   */ LD_R_R,
        /*   01 100 110   */ LD_R_pHL,
        /*   01 100 111   */ LD_R_R,
        /*   01 101 000   */ LD_R_R,
        /*   01 101 001   */ LD_R_R,
        /*   01 101 010   */ LD_R_R,
        /*   01 101 011   */ LD_R_R,
        /*   01 101 100   */ LD_R_R,
        /*   01 101 101   */ LD_R_R,
        /*   01 101 110   */ LD_R_pHL,
        /*   01 101 111   */ LD_R_R,
        /*   01 110 000   */ LD_pHL_R,
        /*   01 110 001   */ LD_pHL_R,
        /*   01 110 010   */ LD_pHL_R,
        /*   01 110 011   */ LD_pHL_R,
        /*   01 110 100   */ LD_pHL_R,
        /*   01 110 101   */ LD_pHL_R,
        /*   01 110 110   */ HALT,
        /*   01 110 111   */ LD_pHL_R,
        /*   01 111 000   */ LD_R_R,
        /*   01 111 001   */ LD_R_R,
        /*   01 111 010   */ LD_R_R,
        /*   01 111 011   */ LD_R_R,
        /*   01 111 100   */ LD_R_R,
        /*   01 111 101   */ LD_R_R,
        /*   01 111 110   */ LD_R_pHL,
        /*   01 111 111   */ LD_R_R,

        /*   10 000 000   */ ADD_A_R,
        /*   10 000 001   */ ADD_A_R,
        /*   10 000 010   */ ADD_A_R,
        /*   10 000 011   */ ADD_A_R,
        /*   10 000 100   */ ADD_A_R,
        /*   10 000 101   */ ADD_A_R,
        /*   10 000 110   */ ADD_A_pHL,
        /*   10 000 111   */ ADD_A_R,
        /*   10 001 000   */ ADC_A_S,
        /*   10 001 001   */ ADC_A_S,
        /*   10 001 010   */ ADC_A_S,
        /*   10 001 011   */ ADC_A_S,
        /*   10 001 100   */ ADC_A_S,
        /*   10 001 101   */ ADC_A_S,
        /*   10 001 110   */ ADC_A_pHL,
        /*   10 001 111   */ ADC_A_S,
        /*   10 010 000   */ SUB_S,
        /*   10 010 001   */ SUB_S,
        /*   10 010 010   */ SUB_S,
        /*   10 010 011   */ SUB_S,
        /*   10 010 100   */ SUB_S,
        /*   10 010 101   */ SUB_S,
        /*   10 010 110   */ SUB_pHL,
        /*   10 010 111   */ SUB_S,
        /*   10 011 000   */ SBC_A_S,
        /*   10 011 001   */ SBC_A_S,
        /*   10 011 010   */ SBC_A_S,
        /*   10 011 011   */ SBC_A_S,
        /*   10 011 100   */ SBC_A_S,
        /*   10 011 101   */ SBC_A_S,
        /*   10 011 110   */ SBC_A_pHL,
        /*   10 011 111   */ SBC_A_S,
        /*   10 100 000   */ AND_S,
        /*   10 100 001   */ AND_S,
        /*   10 100 010   */ AND_S,
        /*   10 100 011   */ AND_S,
        /*   10 100 100   */ AND_S,
        /*   10 100 101   */ AND_S,
        /*   10 100 110   */ AND_pHL,
        /*   10 100 111   */ AND_S,
        /*   10 101 000   */ XOR_S,
        /*   10 101 001   */ XOR_S,
        /*   10 101 010   */ XOR_S,
        /*   10 101 011   */ XOR_S,
        /*   10 101 100   */ XOR_S,
        /*   10 101 101   */ XOR_S,
        /*   10 101 110   */ XOR_pHL,
        /*   10 101 111   */ XOR_S,
        /*   10 110 000   */ OR_S,
        /*   10 110 001   */ OR_S,
        /*   10 110 010   */ OR_S,
        /*   10 110 011   */ OR_S,
        /*   10 110 100   */ OR_S,
        /*   10 110 101   */ OR_S,
        /*   10 110 110   */ OR_pHL,
        /*   10 110 111   */ OR_S,
        /*   10 111 000   */ CP_S,
        /*   10 111 001   */ CP_S,
        /*   10 111 010   */ CP_S,
        /*   10 111 011   */ CP_S,
        /*   10 111 100   */ CP_S,
        /*   10 111 101   */ CP_S,
        /*   10 111 110   */ CP_pHL,
        /*   10 111 111   */ CP_S,
        /*   11 000 000   */ RET_CC,
        /*   11 000 001   */ POP_QQ,
        /*   11 000 010   */ JP_CC_NN,
        /*   11 000 011   */ JP_NN,
        /*   11 000 100   */ CALL_CC_NN,
        /*   11 000 101   */ PUSH_QQ,
        /*   11 000 110   */ ADD_A_N,
        /*   11 000 111   */ RST_P,
        /*   11 001 000   */ RET_CC,
        /*   11 001 001   */ RET,
        /*   11 001 010   */ JP_CC_NN,
        /*   11 001 011   */ RunCommandWithPrefixCB,
        /*   11 001 100   */ CALL_CC_NN,
        /*   11 001 101   */ CALL_NN,
        /*   11 001 110   */ ADC_A_N,
        /*   11 001 111   */ RST_P,
        /*   11 010 000   */ RET_CC,
        /*   11 010 001   */ POP_QQ,
        /*   11 010 010   */ JP_CC_NN,
        /*   11 010 011   */ OUT_pN_A,
        /*   11 010 100   */ CALL_CC_NN,
        /*   11 010 101   */ PUSH_QQ,
        /*   11 010 110   */ SUB_N,
        /*   11 010 111   */ RST_P,
        /*   11 011 000   */ RET_CC,
        /*   11 011 001   */ EXX,
        /*   11 011 010   */ JP_CC_NN,
        /*   11 011 011   */ IN_A_pN,
        /*   11 011 100   */ CALL_CC_NN,
        /*   11 011 101   */ RunCommandWithPrefixDD,
        /*   11 011 110   */ SBC_A_N,
        /*   11 011 111   */ RST_P,
        /*   11 100 000   */ RET_CC,
        /*   11 100 001   */ POP_QQ,
        /*   11 100 010   */ JP_CC_NN,
        /*   11 100 011   */ EX_pSP_HL,
        /*   11 100 100   */ CALL_CC_NN,
        /*   11 100 101   */ PUSH_QQ,
        /*   11 100 110   */ AND_N,
        /*   11 100 111   */ RST_P,
        /*   11 101 000   */ RET_CC,
        /*   11 101 001   */ JP_pHL,
        /*   11 101 010   */ JP_CC_NN,
        /*   11 101 011   */ EX_DE_HL,
        /*   11 101 100   */ CALL_CC_NN,
        /*   11 101 101   */ RunCommandWithPrefixED,
        /*   11 101 110   */ XOR_N,
        /*   11 101 111   */ RST_P,
        /*   11 110 000   */ RET_CC,
        /*   11 110 001   */ POP_QQ,
        /*   11 110 010   */ JP_CC_NN,
        /*   11 110 011   */ DI,
        /*   11 110 100   */ CALL_CC_NN,
        /*   11 110 101   */ PUSH_QQ,
        /*   11 110 110   */ OR_N,
        /*   11 110 111   */ RST_P,
        /*   11 111 000   */ RET_CC,
        /*   11 111 001   */ LD_SP_HL,
        /*   11 111 010   */ JP_CC_NN,
        /*   11 111 011   */ EI,
        /*   11 111 100   */ CALL_CC_NN,
        /*   11 111 101   */ RunCommandWithPrefixFD,
        /*   11 111 110   */ CP_N,
        /*   11 111 111   */ RST_P
    };

    AddOpcode(RAM8(PC));

    return firstLevel[PCandInc()]();
}
