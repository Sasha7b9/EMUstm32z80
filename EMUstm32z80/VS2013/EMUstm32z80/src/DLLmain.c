#include "DLLmain.h"


#pragma warning(push)
#pragma warning(disable:4255)
#pragma warning(disable:4820)
#pragma warning(disable:4668)
#include <Windows.h>
#pragma warning(pop)


#include "CPU/instr.h"
#include "CPU/registers.h"
#include "common.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OutStruct *out = 0;

uint8 *RAM = 0;


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
__declspec(dllexport) void __cdecl InitEMU(OutStruct *out_)
{
    out = out_;
    out->regs = &regs;
    out->regsAlt = &regsAlt;
    RAM = out->RAM;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
__declspec(dllexport) int __cdecl Decode(int address)
{
    out->numAddresses = 0;
    out->numOpCodes = 0;
    TRANSCRIPT[0] = 0;
    out->flags[0] = 0;
    out->tackts = 0;
    out->comment[0] = 0;

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
