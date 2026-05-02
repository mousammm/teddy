#pragma once
#include "common.h"

#define MAX_MEM 0x10000

typedef struct 
{
  u8 Data[MAX_MEM];
} MEM;

typedef struct 
{
  u16 PC;   /* Program Counter */
  u16 SP;   /* Stack pointer */
  u8  AC, XR, YR;  /* Register */

  u8 C; u8 Z; u8 I; u8 D;
  u8 B; u8 V; u8 N; 
} CPU;

void CPU_Reset(CPU *cpu);
void MEM_Init(MEM *mem);
