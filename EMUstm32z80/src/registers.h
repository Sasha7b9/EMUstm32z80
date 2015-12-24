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
    RF = 8,
    RI = 9,     // Interrupt register
    RR = 10     // Regeneration register
} REG_8;

typedef enum
{
    RPC = 0
} REG_16;

typedef enum
{
    RQQ_BC = 0,
    RQQ_DE = 1,
    RQQ_HL = 2,
    RQQ_AF = 3
} REG_QQ;

typedef enum
{
    RDD_BC = 0,
    RDD_DE = 1,
    RDD_HL = 2,
    RDD_SP = 3
}REG_DD;


// Return value from RAM, pointed to PC, and increment PC
uint8 PCandInc(void);
uint16 PCandInc16(void);
uint8 PrevPC(void);

uint8 GetReg8(REG_8 reg);
void LoadReg8(REG_8 dest, uint8 value);

uint16 GetRegQQ(REG_QQ reg);
uint16 GetRegDD(REG_DD reg);
void LoadRegDD(REG_DD reg, uint16 value);
void LoadRegQQ(REG_QQ reg, uint16 value);

void ExchangeReg8(REG_8 reg);

uint8 CY(void);
