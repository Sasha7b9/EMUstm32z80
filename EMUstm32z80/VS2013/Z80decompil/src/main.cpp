#include "stdafx.h"
#include "DataBase.h"


extern "C"
{
    #include "DLLmain.h"
    #include "RAM.h"
}


#pragma comment(lib, "EMUstm32z80.lib")


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char mnemonic[100];
char comment[100];
char flags[100];
char transcript[100];
uint16 addresses[10];
int numAddresses;
uint8 opCodes[10];
int numOpCodes;
int tackts;


DataBase base;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    Init(RAM, mnemonic, comment, flags, transcript, addresses, &numAddresses, opCodes, &numOpCodes, &tackts);

    int address = base.NextAddress();

    while(address >= 0)
    {
        bool res = Decode((uint16)address) != 0;

        base.AddNewData(res, address, mnemonic, comment, flags, transcript, addresses, numAddresses, opCodes, numOpCodes, tackts);

        address = base.NextAddress();
    }

    base.CreateReport();
}