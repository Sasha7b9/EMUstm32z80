#pragma once


#pragma warning(push)
#pragma warning(disable:4820)


#define ADDR_C 0
#define ADDR_B 1
#define ADDR_E 2
#define ADDR_D 3
#define ADDR_L 4
#define ADDR_H 5
#define ADDR_F 6
#define ADDR_A 7

#define ADDR_BC 0
#define ADDR_DE 1
#define ADDR_HL 2
#define ADDR_AF 3
#define ADDR_SP 4
#define ADDR_IX 5
#define ADDR_IY 6
#define ADDR_PC 7


typedef union
{
    unsigned char r8[8];    // C B  E D  L H  F A
    unsigned short r16[8];  // BC   DE   HL   AF    SP  IX  IY  PC
} REGS;


typedef struct
{
    unsigned char *RAM;
    char mnemonic[100];
    char comment[100];
    char flags[100];
    char transcript[100];
    unsigned int addresses[10];
    int numAddresses;
    unsigned char opCodes[10];
    int numOpCodes;
    int tackts;
    REGS *regs;
    REGS *regsAlt;
} OutStruct;


__declspec(dllexport) void __cdecl InitEMU(OutStruct *out);
__declspec(dllexport) int __cdecl Decode(int address);  // ret value : 0 - unknown command, else - successful
__declspec(dllexport) int __cdecl Run(int address);     // ret value : 0 - unknown command, else - successful
__declspec(dllexport) int __cdecl RunNext(void);        // ret value : 0 - unknown command, else - successful


#pragma warning(pop)
