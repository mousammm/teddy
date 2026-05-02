#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "fillMem.h"

typedef enum {
  IMMEDIATE = 2,
  ABSOLUTE = 3,
} mode;

typedef enum {
  IN_LDA,
  IN_LDX,
  IN_LDY,
} ins;

typedef struct {
  ins ins;
  mode mode;
  void (*IN_FUN)();
} INS;

/* instruction function */
void LDA() {
  u8 val = RAM[cpu.pc+1];
  cpu.a = val;
}

void LDX() {
  u8 val = RAM[cpu.pc+1];
  cpu.x = val;
}

void LDY() {
  u8 val = RAM[cpu.pc+1];
  cpu.y = val;
}

void STA() {
  /* store the accumelator */
  u8 lsb = RAM[cpu.pc+1];
  u8 msb = RAM[cpu.pc+2];
  u16 loc = msb * 256 + lsb;

  RAM[loc] = cpu.a;
}

void STX() {
  /* store the x*/
  u8 lsb = RAM[cpu.pc+1];
  u8 msb = RAM[cpu.pc+2];
  u16 loc = msb * 256 + lsb;

  RAM[loc] = cpu.x;
}

void STY() {
  /* store the y*/
  u8 lsb = RAM[cpu.pc+1];
  u8 msb = RAM[cpu.pc+2];
  u16 loc = msb * 256 + lsb;

  RAM[loc] = cpu.y;
}

/* 256 diff commands */
INS inst[0xFF] = {
  [0xA9] = {IN_LDA, IMMEDIATE, LDA},
};

void tick() {
  /* fetch */
  u8 command = RAM[cpu.pc];
  printf("command: 0x%02x\n", command);

  /* execute */
  if (command == 0xA9) {
    LDA(); cpu.pc+=2;
  }

  if (command == 0x42) {
    LDX(); cpu.pc+=2;
  }

  if (command == 0x40) {
    LDY(); cpu.pc+=2;
  }

  if (command == 0x8D) { /* STA in 0x4400 */
    STA(); cpu.pc+=3;
  }

  if (command == 0x8E) { /* STX in 0x4401 */
    STX(); cpu.pc+=3;
  }

  if (command == 0x8C) { /* STY in 0x4402 */
    STY(); cpu.pc+=3;
  }

}

int main(int argc, char *argv[])
{
  init();
  for (int i=0; i<10; ++i) {
    printf("%hu\n", inst->mode);
    printf("%c\n", inst->ins);
    tick();
  }

  printf("\t CPU info:\n");
  printf("\t cpu.a: %hhu \t 0x%02x\n", cpu.a ,cpu.a);
  printf("\t cpu.x: %hhu \t 0x%02x\n", cpu.x ,cpu.x);
  printf("\t cpu.y: %hhu \t 0x%02x\n", cpu.y ,cpu.y);
  printf("\t cpu.pc: %hu \t 0x%04x\n", cpu.pc, cpu.pc);

  printf("STA ram.0x4400 %hu 0x%02x\n", RAM[0x4400], RAM[0x4400]);
  printf("STX ram.0x4401 %hu 0x%02x\n", RAM[0x4401], RAM[0x4401]);
  printf("STY ram.0x4402 %hu 0x%02x\n", RAM[0x4402], RAM[0x4402]);

  return EXIT_SUCCESS;
}
