#include "instrED.h"

#include "defines.h"

#include "CPU/registers.h"

#include "Hardware/ports.h"

#include <string.h>

#include <stdio.h>

#include "common.h"

#include "RAM.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LD_A_I(void)
{
    return 9;   // WARN
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_I_A(void)
{
#ifdef LISTING

    *tackts = 9;
    AddAddress(PC);

    strcpy(mnemonic, "LD I,A");
    strcpy(transcript, "I<-A");
    strcpy(comment, "I - Interrupt Control Vector Register");

    return -1;

#else

    return 9;   // WARN

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_A_R(void)
{
    return 9;   // WARN
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_R_A(void)
{
    return 9;   // WARN
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_DD_pNN(void)
{
#ifdef LISTING

    AddOpcode(RAM8(PC));
    AddOpcode(RAM8(PC + 1));

    uint8 retValue = prevPC;

    sprintf(mnemonic, "LD %s,[%04X]", DD_45_Name(retValue), PC16andInc());

    AddAddress(PC);

    return -1;

#else

    uint8 valReg = prevPC;
    DD_45(valReg) = RAM16(PC16andInc());
    return 20;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LD_pNN_DD(void)
{
#ifdef LISTING

    *tackts = 20;

    uint8 valDD = prevPC;
    AddOpcode(RAM8(PC));
    AddOpcode(RAM8(PC + 1));
    uint16 address = PC16andInc();
    AddAddress(PC);

    sprintf(mnemonic, "LD [%4X],%s", address, DD_45_Name(valDD));
    sprintf(transcript, "[%4X]<-%s", address, DD_45_Name(prevPC));

    return -1;

#else

    uint valDD = prevPC;
    RAM16(PC16andInc()) = DD_45(valDD);
    return 20;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LDI(void)
{
    RAM16(DE) = RAM16(HL);
    DE += 1;
    HL += 1;
    BC -= 1;
    return 16;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LDIR(void)
{
#ifdef LISTING

    AddAddress(PC);
    strcpy(mnemonic, "LDIR");
    return -1;

#else

    int time = 0;
    do
    {
        LDI();
        time += 21;
    } while(BC != 0);

    return time + 16;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LDD(void)
{
    RAM16(DE) = RAM16(HL);
    DE--;
    HL--;
    BC--;
    return 16;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int LDDR(void)
{
#ifdef LISTING

    AddAddress(PC);
    sprintf(mnemonic, "LDDR");
    return -1;

#else

    int time = 0;

    do
    {
        time += 21;
        LDD();
    } while(BC != 0);

    return time += 16;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int CPI(void)
{
    HL++;
    BC--;

    // + + x + x + 1 .

    // S WARN
    // Z WARN
    // H WARN
    // PV WARN
    SET_N;

    return 16;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int CPIR(void)
{
    int time = 0;

    do
    {
        time += 21;
        CPI();
    } while(BC != 0 && A != RAM8(HL));

    return time + 16;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int CPD(void)
{
    HL--;
    BC--;

    // + + x + x + 1 .
    // S WARN
    // Z WARN
    // H WARN
    // PV WARN
    SET_N;

    return 16;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int CPDR(void)
{
    int time = 0;

    do
    {
        time += 21;
        CPD();
    } while(BC != 0 && A != RAM8(HL));

    return time + 16;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int NEG(void)
{
#ifdef LISTING

    AddAddress(PC);
    strcpy(mnemonic, "NEG");
    return -1;

#else

    A = (~A) + 1;

    // + + x + x V 1 +
    // S WARN
    // Z
    // H
    // V
    SET_N;
    // C

    return 8;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int IM0(void)
{
    return 8;   // WARN
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int IM1(void)
{
#ifdef LISTING

    AddAddress(PC);
    strcpy(mnemonic, "IM1");
    return -1;

#else

    return 8;   // WARN

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int IM2(void)
{
    return 8;   // WARN
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int ADC_HL_SS(void)
{
    HL += SS_45(prevPC) + CF;

    // + + x x x V 0 +
    // S
    // Z    WARN
    // V
    RES_N;
    // C

    return 15;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int SBC_HL_SS(void)
{
#ifdef LISTING

    *tackts = 15;
    AddAddress(PC);
    strcpy(flags, "++XXXV1+");
    sprintf(mnemonic, "SBC HL,%s", SS_45_Name(prevPC));
    sprintf(transcript, "HL<-HL-%s-CY", SS_45_Name(prevPC));
    return -1;

#else

    HL -= SS_45(prevPC) - CF;

    // + + x x x V 1 +
    // S
    // Z    WARN
    // V
    SET_N;
    // C

    return 15;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RLD(void)
{
    uint8 val_pHL = RAM8(HL);
    uint8 pHLlow = val_pHL & 0x0f;
    uint8 pHLhi = (val_pHL >> 4) & 0x0f;
    uint8 Alow = A & 0x0f;

    val_pHL = 0;
    A &= 0x0f;

    val_pHL |= Alow;        // low pHL
    val_pHL |= pHLlow << 4; // hi pHL
    A |= pHLhi;

    RAM8(HL) = val_pHL;

    // + + x 0 x P 0 .
    // S    WARN
    // Z
    RES_H;
    // P
    RES_N;

    return 18;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RRD(void)
{
    uint8 val_pHL = RAM8(HL);
    uint8 pHLlow = val_pHL & 0x0f;
    uint8 pHLhi = (val_pHL >> 4) & 0x0f;
    uint8 Alow = A & 0x0f;

    val_pHL = 0;
    A &= 0x0f;

    val_pHL |= pHLhi;
    val_pHL |= Alow << 4;
    A |= pHLlow;

    RAM8(HL);

    // + + x 0 x P 0 .
    // S    WARN
    // Z
    RES_H;
    // P
    RES_N;

    return 18;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RETN(void)
{
    return 14;  // WARN
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int IN_R_pC(void)
{
#ifdef LISTING

    if(((prevPC >> 3) & 7) != 6)
    {
        sprintf(mnemonic, "IN %s,(C)", R8_HI_Name(prevPC));
        sprintf(transcript, "%s<-(C)", R8_HI_Name(prevPC));
        strcpy(comment, "C - A0...A7, B - A8...A15");
    }
    else
    {
        strcpy(mnemonic, "IN (HL), (C); R == 110, set flags only");
    }
    strcpy(flags, "+ + X + X P 0 .");
    AddAddress(PC);

    return -1;
#else

    if(((prevPC >> 3) & 7) == 6)
    {

    }
    else
    {
        R8_HI(prevPC) = ReadPort(C);
    }

    // + + x + x P 0 .
    // S
    // Z    WARN
    // H
    // P
    RES_N;

    return 12;
#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int INI(void)
{
#ifdef LISTING

    strcpy(mnemonic, "INI");
    strcpy(comment, "C - A0...A7, B - A8...A15; if B-1==0, Z set, else reset");
    strcpy(flags, "X + X X X X 1 X");
    strcpy(transcript, "(HL)<-(C); B--; HL++");
    AddAddress(PC);
    return 0;

#else

    return 0;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int INIR(void)
{
#ifdef LISTING

    strcpy(mnemonic, "INIR");
    strcpy(comment, "C - A0...A7, B - A8...A15; z set only after finishing instruction");
    strcpy(flags, "X 1 X X X X X 1 ");
    strcpy(transcript, "(HL)<-(C); B--; HL++; while B!=0");
    AddAddress(PC);
    return 0;

#else

    return 0;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int IND(void)
{
#ifdef LISTING

    strcpy(mnemonic, "IND");
    strcpy(transcript, "(HL)<-(C); B--; HL--");
    AddAddress(PC);
    return 0;

#else

    return 0;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int INDR(void)
{
#ifdef LISTING

    strcpy(mnemonic, "INDR");
    strcpy(transcript, "(HL)<-(C); B--; HL--; while B!=0");
    AddAddress(PC);
    return 0;

#else

    return 0;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int OUT_pC_R(void)
{
#ifdef LISTING

    sprintf(mnemonic, "OUT (C), %s", R8_HI_Name(prevPC));
    sprintf(transcript, "(C)<-%s", R8_HI_Name(prevPC));
    return 0;

#else

    return 0;

#endif
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
#include "FuncSecondED.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------
int RunCommandWithPrefixED(void)
{
    AddOpcode(RAM8(PC));

    int index = PCandInc();

    if(secondLevelED[index][0] == 0)
    {
        return 0;
    }

    return secondLevelED[index][0]();
}
