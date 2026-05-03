#include "cpu.h"

u16 p = 0x1000; /* same as program counter */
void pushMC(RAM *ram, u8 MC) {
  /* TODO: check if p > 0x10,000 | 0xFFFF */
  ram->RAM[p] = MC;
  p++;
}

void initRAM(RAM *ram) {
  for (int i=0; i<0x10000; ++i){
    ram->RAM[i] = 0;
  }

  pushMC(ram, 0xA9); /* LDA $A9 #$0A */
  pushMC(ram, 0x0A);

  pushMC(ram, 0xA2); /* LDX $A2 #$0B */
  pushMC(ram, 0x0B);

  pushMC(ram, 0xA0); /* LDY $A0 #$0C */
  pushMC(ram, 0x0C);

  pushMC(ram, 0x8D); /* STA $8D $4400(Absolute) */
  pushMC(ram, 0x00); /* lsb 1st (little endine) */
  pushMC(ram, 0x44); /* msb 2nd */

  pushMC(ram, 0x8E); /* STX $8E $4401(Absolute) */
  pushMC(ram, 0x01); /* lsb 1st (little endine) */
  pushMC(ram, 0x44); /* msb 2nd */

  pushMC(ram, 0x8C); /* STY $8C $4402(Absolute) */
  pushMC(ram, 0x02); /* lsb 1st (little endine) */
  pushMC(ram, 0x44); /* msb 2nd */

  // pushMC(ram, 0xE8); /* INX x reg ++ */
  // pushMC(ram, 0xC8); /* INY y reg ++ */
  // pushMC(ram, 0xCA); /* DEX x reg -- */
  // pushMC(ram, 0x88); /* DEY y reg -- */

  // pushMC(ram, 0xAA); /* TAX x = a*/
  // pushMC(ram, 0xA8); /* TAY y = a*/
  // pushMC(ram, 0x8A); /* TXA a = x*/
  // pushMC(ram, 0x98); /* TYA a = y*/

  // pushMC(ram, 0xBD); /* LDA_X (AC = 4401 + X)*/
  // pushMC(ram, 0x01);
  // pushMC(ram, 0x44);

  // pushMC(ram, 0xB9); /* LDA_Y (AC = 4401 + Y)*/
  // pushMC(ram, 0x01);
  // pushMC(ram, 0x44);

}

