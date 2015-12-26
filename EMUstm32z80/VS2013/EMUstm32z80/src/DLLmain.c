#include "DLLmain.h"


#pragma warning(push)
#pragma warning(disable:4255)
#pragma warning(disable:4820)
#pragma warning(disable:4668)
#include <Windows.h>
#pragma warning(pop)


#include "CPU/instr.h"


uint8 *RAM;
char *mnemonic;
char *comment;
char *flags;
char *transcript;
uint16 *addresses;
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
    uint16 eAddresses[10],
    int *eNumAddresses,
    uint8 eOpCodes[10],
    int *eNumOpCodes,
    int eTackts[1]
)
{
    RAM = eRAM;
    mnemonic = eMnemonic;
    comment = eComment;
    flags = eFlags;
    transcript = eTranscript;

    addresses = eAddresses;
    numAddresses = eNumAddresses;
    *numAddresses = 0;

    opCodes = eOpCodes;
    numOpCodes = eNumOpCodes;
    *numOpCodes = 0;

    tackts = eTackts;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
__declspec(dllexport) void Decode(uint16 address)
{

}
