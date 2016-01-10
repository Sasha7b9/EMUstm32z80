#pragma once


#include "defines.h"
#include "DLLmain.h"


extern OutStruct *out;


#define TACKTS  out->tackts
#define FLAGS   out->flags
#define COMMENT out->comment

void AddAddress(uint address);
void AddOpcode(uint8 code);
