#pragma once


#pragma warning(push)
#pragma warning(disable:4820)


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
