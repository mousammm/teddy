#pragma once
#include "common.h"

typedef struct {
  u8 RAM[0x10000];
} RAM;

typedef struct {
  u8 AC;      /* accumulator */
  u8 XR, YR;  /* x and y register */
  u16 PC;     /* program counter */
} CPU;

void initRAM(RAM *ram);

static void initCPU(CPU *cpu) {
  cpu->AC = 0x0;
  cpu->XR = 0x0;
  cpu->YR = 0x0;
  cpu->PC = 0x1000;
}

