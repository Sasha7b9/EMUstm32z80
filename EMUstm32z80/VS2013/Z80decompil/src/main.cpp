#include "stdafx.h"
#include "DataBase.h"


extern "C"
{
    #include "DLLmain.h"
    #include "RAM48.h"
}


#pragma comment(lib, "EMUstm32z80.lib")


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DataBase base;

OutStruct params;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    params.RAM = RAM48;

    InitEMU(&params);

    int address = base.NextAddress();

    while(address >= 0)
    {
        bool res = Decode((uint16)address) != 0;

        base.AddNewData(res, address, &params);

        address = base.NextAddress();
    }

    base.CreateReport();
}