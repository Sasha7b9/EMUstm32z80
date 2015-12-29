#pragma once


typedef enum
{
    Operand_A,
    Operand_Reg8,
    Operand_pHL,
    Operand_IX,
    Operand_IY
} TypeOperand;


int RLC(TypeOperand type);

int RRC(TypeOperand type);
