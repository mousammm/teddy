#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"

CPU cpu;
RAM ram;

/* tick */
void tick(CPU *cpu, RAM *ram) {
  u8 command = ram->RAM[cpu->PC];

  if (command == 0xA9) { /* LDA $A9 $44 */
    LDA(cpu, ram); /* mode: immediate */
    cpu->PC += 2;
  }

  if (command == 0xA2) { /* LDX $A2 $45 */
    LDX(cpu, ram); /* mode: immediate */
    cpu->PC += 2;
  }

  if (command == 0xA0) { /* LDY $A0 $46 */
    LDY(cpu, ram); /* mode: immediate */
    cpu->PC += 2;
  }

  if (command == 0x8D) { /* STA $8D $4400 */
    STA(cpu, ram); /* mode: immediate */
    cpu->PC += 3;
  }

  if (command == 0x8E) { /* STX $8E $4401 */
    STX(cpu, ram); /* mode: immediate */
    cpu->PC += 3;
  }

  if (command == 0x8C) { /* STY $8C $4402 */
    STY(cpu, ram); /* mode: immediate */
    cpu->PC += 3;
  }

};

int main(int argc, char *argv[])
{
  initCPU(&cpu);
  initRAM(&ram);

  for (int i = 0; i < 100; ++i) {
    tick(&cpu, &ram);
  };

  printf("\t AC: %hu 0x%02x\n", cpu.AC, cpu.AC);
  printf("\t XR: %hu 0x%02x\n", cpu.XR, cpu.XR);
  printf("\t YR: %hu 0x%02x\n", cpu.YR, cpu.YR);
  printf("\t PC: %hu 0x%02x\n", cpu.PC, cpu.PC);

  printf("\n\t STA: %hu 0x%02x\n", ram.RAM[0x4400], ram.RAM[0x4400]);
  printf("\t STX: %hu 0x%02x\n", ram.RAM[0x4401], ram.RAM[0x4401]);
  printf("\t STX: %hu 0x%02x\n", ram.RAM[0x4402], ram.RAM[0x4402]);

  printf("\t 0x%02x\n", ram.RAM[0x1000]);

  return EXIT_SUCCESS;
}
