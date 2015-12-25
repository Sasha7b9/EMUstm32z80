#pragma once


#include "defines.h"


typedef union
{
    //              C B   E D   L H   F A
    uint8   r8[8];
    //              BC    DE    HL    AF    SP
    uint16  r16[5];
} REGS;


typedef enum
{
    RB_ = 0,
    RC_ = 1,
    RD_ = 2,
    RE_ = 3,
    RH_ = 4,
    RL_ = 5,
    pHL_ = 6,
    RA_ = 7
} REG_8;


typedef enum
{
    RQQ_BC_ = 0,
    RQQ_DE_ = 1,
    RQQ_HL_ = 2,
    RQQ_AF_ = 3
} REG_QQ;


// Return value from RAM, pointed to PC, and increment PC
uint8 PCandInc(void);
uint16 PC16andInc(void);


extern uint8 prevPC;
extern pFuncpU8V funcsReg8[8];
extern pFuncpU16V funcsRegDD[4];
extern REGS regs;
extern REGS regsAlt;
extern uint8 regI;
extern uint8 regR;


#define CY      (regs.r8[6] & 0x01)

#define BC      regs.r16[0]
#define DE      regs.r16[1]
#define HL      regs.r16[2]
#define AF      regs.r16[3]
#define SP      regs.r16[4]

#define A       regs.r8[7]
#define B       regs.r8[1]
#define C       regs.r8[0]
#define D       regs.r8[3]
#define E       regs.r8[2]
#define L       regs.r8[4]
#define H       regs.r8[5]
#define pHL     RAM[regs.r16[2]]
#define F       (regs.r8[6])
#define I       regI
#define R       regR

#define Aalt    regsAlt.r8[7]
#define Balt    regsAlt.r8[1]
#define RCalt   regsAlt.r8[0]
#define RDalt   regsAlt.r8[3]
#define REalt   regsAlt.r8[2]
#define RLalt   regsAlt.r8[4]
#define RHalt   regsAlt.r8[5]
#define RFalt   regsAlt.r8[6]

#define R8_HI(value)    (*funcsReg8[(value >> 3) & 7]())
#define R8_LO(value)    (*funcsReg8[value & 7]())

#define DD_45(value)    (*funcsRegDD[(value >> 4) & 3]())
#define QQ_45(value)    (regs.r16[(value >> 4) & 3])

#define EXCH(r1, r2)    \
    temp = r1;          \
    r1 = r2;            \
    r2 = temp;
