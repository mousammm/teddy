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

typedef void (*InsFun)(CPU*, RAM*);
typedef struct {
  InsFun  func;
  u8      pc_inc;
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
