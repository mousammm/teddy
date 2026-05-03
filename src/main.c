#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"

CPU cpu;
RAM ram;

Instruction INS[0x100] = {

  /* Load the accumulator */
  [0xA9] = (Instruction){LDA, IMMEDIATE},
  [0xA5] = (Instruction){LDA_ZP, ZERO_PAGE},
  [0xB5] = (Instruction){LDA_ZP_X, ZERO_PAGE_X},
  [0xAD] = (Instruction){LDA_A, ABSOLUTE},
  [0xBD] = (Instruction){LDA_X, ABSOLUTE_X},
  [0xB9] = (Instruction){LDA_Y, ABSOLUTE_Y},

  [0xA2] = (Instruction){LDX, IMMEDIATE},
  [0xA0] = (Instruction){LDY, IMMEDIATE},

  [0x8D] = (Instruction){STA, ABSOLUTE},
  [0x8E] = (Instruction){STX, ABSOLUTE},
  [0x8C] = (Instruction){STY, ABSOLUTE},

  [0xE8] = (Instruction){INX, IMPLIED},
  [0xC8] = (Instruction){INY, IMPLIED},
  [0xCA] = (Instruction){DEX, IMPLIED},
  [0x88] = (Instruction){DEY, IMPLIED},
  [0xAA] = (Instruction){TAX, IMPLIED},
  [0xA8] = (Instruction){TAY, IMPLIED},
  [0x8A] = (Instruction){TXA, IMPLIED},
  [0x98] = (Instruction){TYA, IMPLIED},

};

/* tick */
void tick(CPU *cpu, RAM *ram) {
  u8 command = ram->RAM[cpu->PC];

  Instruction *inst = &INS[command];
  // printf("cmd: %d\n", inst->pc_inc);

  if (inst->func) {
    inst->func(cpu, ram);
    cpu->PC += inst->mode;
  } else {
    // printf("Unknown opcode: 0x%02x\n", command);
    cpu->PC++;
  }

};

int main(int argc, char *argv[])
{

  initCPU(&cpu);
  initRAM(&ram);

  for (int i = 0; i < 20; ++i) {
    tick(&cpu, &ram);
  };

  printf("\t AC: %hu 0x%02x\n", cpu.AC, cpu.AC);
  printf("\t XR: %hu 0x%02x\n", cpu.XR, cpu.XR);
  printf("\t YR: %hu 0x%02x\n", cpu.YR, cpu.YR);
  printf("\t PC: %hu 0x%02x\n", cpu.PC, cpu.PC);

  printf("\n");

  printf("\t STA: %hu 0x%02x\n", ram.RAM[0x4400], ram.RAM[0x4400]);
  printf("\t STX: %hu 0x%02x\n", ram.RAM[0x4401], ram.RAM[0x4401]);
  printf("\t STX: %hu 0x%02x\n", ram.RAM[0x4402], ram.RAM[0x4402]);

  return EXIT_SUCCESS;
}
