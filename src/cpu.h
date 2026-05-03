#pragma once
#include "common.h"
#include <stdio.h>

typedef struct {
  u8 RAM[0x10000];
} RAM;

typedef struct {
  u8 AC;      /* accumulator */
  u8 XR, YR;  /* x and y register */
  u16 PC;     /* program counter */
} CPU;

typedef enum {
  IMMEDIATE   = 2,

  ZERO_PAGE   = 2, /* 1st 256 bytes of ram */
  ZERO_PAGE_X = 2, /* 1st 256 bytes of ram */

  ABSOLUTE    = 3,
  ABSOLUTE_X  = 3,
  ABSOLUTE_Y  = 3,

  IMPLIED     = 1,
} MODE;

typedef void (*InsFun)(CPU*, RAM*);
typedef struct {
  InsFun  func;
  MODE    mode;
} Instruction;

void initRAM(RAM *ram);
static void initCPU(CPU *cpu) {
  cpu->AC = 0x0;
  cpu->XR = 0x0;
  cpu->YR = 0x0;
  cpu->PC = 0x1000;
}

/* LDA $49 $44 (Immediate) */
static void LDA(CPU *cpu, RAM *ram) {
  u8 val = ram->RAM[cpu->PC+1];
  cpu->AC = val;
};

static void LDA_ZP(CPU *cpu, RAM *ram) {
 /* load ac = ram(loc) */
  u16 loc = ram->RAM[cpu->PC+1];
  printf("Zero Page: 0x%04x\n", loc);
};

static void LDA_ZP_X(CPU *cpu, RAM *ram) {
 /* load ac = ram(loc+x) */
  u16 loc = ram->RAM[cpu->PC+1];
  printf("Zero Page X: 0x%04x\n", loc+cpu->XR);
};

static void LDA_A(CPU *cpu, RAM *ram) {
  u8 lsb = ram->RAM[cpu->PC+1];
  u8 msb = ram->RAM[cpu->PC+2];
  u16 loc = msb * 256 + lsb;

  cpu->AC = ram->RAM[loc];
};

static void LDA_X(CPU *cpu, RAM *ram) {
  u8 lsb = ram->RAM[cpu->PC+1];
  u8 msb = ram->RAM[cpu->PC+2];
  u16 loc = msb * 256 + lsb;
  loc += cpu->XR;

  cpu->AC = ram->RAM[loc];
};

static void LDA_Y(CPU *cpu, RAM *ram) {
  u8 lsb = ram->RAM[cpu->PC+1];
  u8 msb = ram->RAM[cpu->PC+2];
  u16 loc = msb * 256 + lsb;
  loc += cpu->YR;

  cpu->AC = ram->RAM[loc];
};

/* LDX $4@ $45 (Immediate) */
static void LDX(CPU *cpu, RAM *ram) {
  u8 val = ram->RAM[cpu->PC+1];
  cpu->XR = val;
};

/* LDY $40 $46 (Immediate) */
static void LDY(CPU *cpu, RAM *ram) {
  u8 val = ram->RAM[cpu->PC+1];
  cpu->YR = val;
};

/* STA $8D $4400(Absolute) */
static void STA(CPU *cpu, RAM *ram) {
  u8 lsb = ram->RAM[cpu->PC+1];
  u8 msb = ram->RAM[cpu->PC+2];
  u16 loc = msb * 256 + lsb;

  ram->RAM[loc] = cpu->AC;
};

/* STX $8E $4401(Absolute) */
static void STX(CPU *cpu, RAM *ram) {
  u8 lsb = ram->RAM[cpu->PC+1];
  u8 msb = ram->RAM[cpu->PC+2];
  u16 loc = msb * 256 + lsb;

  ram->RAM[loc] = cpu->XR;
};

/* STY $8C $4403(Absolute) */
static void STY(CPU *cpu, RAM *ram) {
  u8 lsb = ram->RAM[cpu->PC+1];
  u8 msb = ram->RAM[cpu->PC+2];
  u16 loc = msb * 256 + lsb;

  ram->RAM[loc] = cpu->YR;
};

/* inc x and y */
static void INX(CPU *cpu, RAM *ram) { cpu->XR++; }
static void INY(CPU *cpu, RAM *ram) { cpu->YR++; }
static void DEX(CPU *cpu, RAM *ram) { cpu->XR--; }
static void DEY(CPU *cpu, RAM *ram) { cpu->YR--; }
/* transfer x/y with a */
static void TAX(CPU *cpu, RAM *ram) { cpu->XR = cpu->AC; } /* x = a */
static void TAY(CPU *cpu, RAM *ram) { cpu->YR = cpu->AC; } /* y = a */
static void TXA(CPU *cpu, RAM *ram) { cpu->AC = cpu->XR; } /* a = x */
static void TYA(CPU *cpu, RAM *ram) { cpu->AC = cpu->YR; } /* a = y */
