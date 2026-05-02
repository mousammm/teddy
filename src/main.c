#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"

CPU cpu;
u8 MEM[0x10000] = {
  [0x1000] = 0xA9, /* LDA $A9 $44 */
  [0x1001] = 0x44,

  [0x1002] = 0xA2, /* LDX $A2 $45 */
  [0x1003] = 0x45,

  [0x1004] = 0xA0, /* LDY $A0 $46 */
  [0x1005] = 0x46,

  [0x1006] = 0x8D, /* STA $8D $4400(Absolute) */
  [0x1007] = 0x00, /* lsb 1st (little endine) */
  [0x1008] = 0x44, /* msb 2nd */

  [0x1009] = 0x8E, /* STX $8E $4401(Absolute) */
  [0x100A] = 0x01, /* lsb 1st (little endine) */
  [0x100B] = 0x44, /* msb 2nd */

  [0x100C] = 0x8C, /* STY $8C $4402(Absolute) */
  [0x100D] = 0x02, /* lsb 1st (little endine) */
  [0x100E] = 0x44, /* msb 2nd */

};

/* LDA $49 $44 (Immediate) */
void LDA(CPU *cpu) {
  u8 val = MEM[cpu->PC+1];
  cpu->AC = val;
};

/* LDX $4@ $45 (Immediate) */
void LDX(CPU *cpu) {
  u8 val = MEM[cpu->PC+1];
  cpu->XR = val;
};

/* LDY $40 $46 (Immediate) */
void LDY(CPU *cpu) {
  u8 val = MEM[cpu->PC+1];
  cpu->YR = val;
};

/* STA $8D $4400(Absolute) */
void STA(CPU *cpu) {
  u8 lsb = MEM[cpu->PC+1];
  u8 msb = MEM[cpu->PC+2];
  u16 loc = msb * 256 + lsb;

  MEM[loc] = cpu->AC;
};

/* STX $8E $4401(Absolute) */
void STX(CPU *cpu) {
  u8 lsb = MEM[cpu->PC+1];
  u8 msb = MEM[cpu->PC+2];
  u16 loc = msb * 256 + lsb;

  MEM[loc] = cpu->XR;
};

/* STY $8C $4403(Absolute) */
void STY(CPU *cpu) {
  u8 lsb = MEM[cpu->PC+1];
  u8 msb = MEM[cpu->PC+2];
  u16 loc = msb * 256 + lsb;

  MEM[loc] = cpu->YR;
};

/* tick */
void tick(CPU *cpu) {
  u8 command = MEM[cpu->PC];

  if (command == 0xA9) { /* LDA $A9 $44 */
    LDA(cpu); /* mode: immediate */
    cpu->PC += 2;
  }

  if (command == 0xA2) { /* LDX $A2 $45 */
    LDX(cpu); /* mode: immediate */
    cpu->PC += 2;
  }

  if (command == 0xA0) { /* LDY $A0 $46 */
    LDY(cpu); /* mode: immediate */
    cpu->PC += 2;
  }

  if (command == 0x8D) { /* STA $8D $4400 */
    STA(cpu); /* mode: immediate */
    cpu->PC += 3;
  }

  if (command == 0x8E) { /* STX $8E $4401 */
    STX(cpu); /* mode: immediate */
    cpu->PC += 3;
  }

  if (command == 0x8C) { /* STY $8C $4402 */
    STY(cpu); /* mode: immediate */
    cpu->PC += 3;
  }

};

int main(int argc, char *argv[])
{
  initCPU(&cpu);

  for (int i = 0; i < 100; ++i) {
    tick(&cpu);
  };

  printf("\t AC: %hu 0x%02x\n", cpu.AC, cpu.AC);
  printf("\t XR: %hu 0x%02x\n", cpu.XR, cpu.XR);
  printf("\t YR: %hu 0x%02x\n", cpu.YR, cpu.YR);
  printf("\t PC: %hu 0x%02x\n", cpu.PC, cpu.PC);

  printf("\n\t STA: %hu 0x%02x\n", MEM[0x4400], MEM[0x4400]);
  printf("\t STX: %hu 0x%02x\n", MEM[0x4401], MEM[0x4401]);
  printf("\t STX: %hu 0x%02x\n", MEM[0x4402], MEM[0x4402]);

  return EXIT_SUCCESS;
}
