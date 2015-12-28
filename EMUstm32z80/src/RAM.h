#pragma once


#include "defines.h"


extern uint8 *RAM;

#define RAM16(address) (*((uint16*)&RAM[address]))
#define RAM8(address) (*(&RAM[address]))
