#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
  u8 a; /* accumulator */
  u8 x; /* index */
  u8 y; /* index */
  u16 pc; /* program counter */
} CPU;

CPU cpu = { 0x00, 0x00, 0x00, 0x1000 };
static u8 RAM[0x10000] = {0};

void init() {
  RAM[0x1000] = 0x49; /* LDA 0x44 */
  RAM[0x1001] = 0x44;

  RAM[0x1002] = 0x42; /* LDX 0x46 */
  RAM[0x1003] = 0x45;

  RAM[0x1004] = 0x40; /* LDY 0x45 */
  RAM[0x1005] = 0x46;

  RAM[0x1006] = 0x8D; /* STA 4400 put backward*/
  RAM[0x1007] = 0x00;
  RAM[0x1008] = 0x44;

  RAM[0x1009] = 0x8E; /* STX 4401 put backward*/
  RAM[0x100A] = 0x01;
  RAM[0x100B] = 0x44;

  RAM[0x100C] = 0x8C; /* STY 4402 put backward*/
  RAM[0x100D] = 0x02;
  RAM[0x100E] = 0x44;
}

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

void tick() {
  /* fetch */
  u8 command = RAM[cpu.pc];
  printf("command: 0x%02x\n", command);

  /* execute */
  if (command == 0x49) {
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
