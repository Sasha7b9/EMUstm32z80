#pragma once


#include "defines.h"


#ifndef LISTING

extern uint8 RAM[65535];

#endif

#define RAM16(address) (*((uint16*)&RAM[address]))
#define RAM8(address) (*(&RAM[address]))
