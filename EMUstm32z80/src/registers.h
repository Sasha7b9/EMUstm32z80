#pragma once


#include "defines.h"


typedef struct
{
    uint8 LOW;
    uint8 HI;
}REG8_;


typedef union
{
    uint16 REG16;
    REG8_  REG8;
} REG;


typedef enum
{
    RB = 0,
    RC = 1,
    RD = 2,
    RE = 3,
    RH = 4,
    RL = 5,
    RpHL = 6,
    RA = 7,
    RI = 8,     // Interrupt register
    RR = 9      // Regeneration register
} REG_8;

typedef enum
{
    RPC = 0
} REG_16;

typedef enum
{
    R_BC = 0,
    R_DE = 1,
    R_HL = 2,
    R_SP = 3
}REG_DD;


// Return value from RAM, pointed to PC, and increment PC
uint8 GetFromPCandInc(void);
uint8 GetPrevPC(void);

uint8 GetReg8(REG_8 reg);
void LoadReg8(REG_8 dest, uint8 value);
