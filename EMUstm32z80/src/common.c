#include "common.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AddAddress(uint16 addr)
{
    addresses[*numAddresses] = addr;
    numAddresses++;
}
