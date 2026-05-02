#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"

CPU cpu;
RAM ram;

Instruction INS[0x100] = {
  [0xA9] = (Instruction){LDA, 2},
  [0xA2] = (Instruction){LDX, 2},
  [0xA0] = (Instruction){LDY, 2},

  [0x8D] = (Instruction){STA, 3},
  [0x8E] = (Instruction){STX, 3},
  [0x8C] = (Instruction){STY, 3},
};

/* tick */
void tick(CPU *cpu, RAM *ram) {
  u8 command = ram->RAM[cpu->PC];

  Instruction *inst = &INS[command];
  // printf("cmd: %d\n", inst->pc_inc);

  if (inst->func) {
    inst->func(cpu, ram);
    cpu->PC += inst->pc_inc;
  } else {
    printf("Unknown opcode: 0x%02x\n", command);
    cpu->PC++;
  }

};

int main(int argc, char *argv[])
{

  initCPU(&cpu);
  initRAM(&ram);

  for (int i = 0; i < 10; ++i) {
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
