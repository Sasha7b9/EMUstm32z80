#pragma once


void Timer_Init(void);

// Start the clock generator
void Timer_StartTicks(void);

// Wait n cycles after the previous call Timer_StartTicks() or Timer_WaitForNTacts()
void Timer_WaitForNTacts(int n);
