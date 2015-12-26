#pragma once

#include "defines.h"

extern uint8 *RAM;
extern char *mnemonic;
extern char *comment;
extern char *flags;
extern char *transcript;
extern uint *addresses;
extern int *numAddresses;
extern uint8 *opCodes;
extern int *numOpCodes;
extern int *tackts;


void AddAddress(uint address);
void AddOpcode(uint8 code);
