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

  ram->RAM[0x100F] = 0xE8; /* INX x reg ++ */
  ram->RAM[0x1010] = 0xC8; /* INY y reg ++ */
  ram->RAM[0x1011] = 0xCA; /* DEX x reg -- */
  ram->RAM[0x1012] = 0x88; /* DEY y reg -- */

  // ram->RAM[0x1013] = 0xAA; /* TAX x = a*/
  // ram->RAM[0x1014] = 0xA8; /* TAY y = a*/
  // ram->RAM[0x1013] = 0x8A; /* TXA a = x*/
  // ram->RAM[0x1013] = 0x98; /* TYA a = y*/

}

