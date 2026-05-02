#include "cpu.h"

void initRAM(RAM *ram) {
  for (int i=0; i<0x10000; ++i){
    ram->RAM[i] = 0;
  }

  ram->RAM[0x1000] = 0xA9; /* LDA $A9 $44 */
  ram->RAM[0x1001] = 0x44;

  ram->RAM[0x1002] = 0xA2; /* LDX $A2 $45 */
  ram->RAM[0x1003] = 0x45;

  ram->RAM[0x1004] = 0xA0; /* LDY $A0 $46 */
  ram->RAM[0x1005] = 0x46;

  ram->RAM[0x1006] = 0x8D; /* STA $8D $4400(Absolute) */
  ram->RAM[0x1007] = 0x00; /* lsb 1st (little endine) */
  ram->RAM[0x1008] = 0x44; /* msb 2nd */

  ram->RAM[0x1009] = 0x8E; /* STX $8E $4401(Absolute) */
  ram->RAM[0x100A] = 0x01; /* lsb 1st (little endine) */
  ram->RAM[0x100B] = 0x44; /* msb 2nd */

  ram->RAM[0x100C] = 0x8C; /* STY $8C $4402(Absolute) */
  ram->RAM[0x100D] = 0x02; /* lsb 1st (little endine) */
  ram->RAM[0x100E] = 0x44; /* msb 2nd */
}

