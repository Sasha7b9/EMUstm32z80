#include "DLLmain.h"


#pragma warning(push)
#pragma warning(disable:4255)
#pragma warning(disable:4820)
#pragma warning(disable:4668)
#include <Windows.h>
#pragma warning(pop)


#include "CPU/instr.h"
#include "CPU/registers.h"


uint8 *RAM;
char *mnemonic;
char *comment;
char *flags;
char *transcript;
uint *addresses;
int *numAddresses;
uint8 *opCodes;
int *numOpCodes;
int *tackts;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__declspec(dllexport) BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    hModule = 0;
    lpReserved = 0;

    switch(ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
__declspec(dllexport) void __cdecl Init
(
    uint8 eRAM[65535],
    char eMnemonic[100],
    char eComment[100],
    char eFlags[100],
    char eTranscript[100],
    uint eAddresses[10],
    int *eNumAddresses,
    uint8 eOpCodes[10],
    int *eNumOpCodes,
    int *eTackts,
    REGS **regs_,
    REGS **regsAlt_
)
{
    RAM = eRAM;
    mnemonic = eMnemonic;
    comment = eComment;
    flags = eFlags;
    transcript = eTranscript;

    addresses = eAddresses;
    numAddresses = eNumAddresses;

    opCodes = eOpCodes;
    numOpCodes = eNumOpCodes;

    tackts = eTackts;

    *regs_ = &regs;
    *regsAlt_ = &regsAlt;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
__declspec(dllexport) int Decode(int address)
{
    *numAddresses = 0;
    *numOpCodes = 0;
    *transcript = 0;
    *flags = 0;
    *tackts = 0;
    *comment = 0;

    PC = (uint16)address;

    // If RunCommand() return >= 0, decoding fail
    return DecodeCommand();
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
__declspec(dllexport) int Run(int address)
{
    PC = (uint16)address;

    return RunCommand();
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
__declspec(dllexport) int RunNext(void)
{
    return RunCommand();
}
