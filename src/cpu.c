#include "cpu.h"

void CPU_Reset(CPU *cpu) {
  cpu->PC = 0xFFFC;
  cpu->SP = 0x0100;
  cpu->AC = cpu->XR = cpu->YR = 0;
}

void MEM_Init(MEM *mem) {
  for (u32 i = 0; i < MAX_MEM; i++) {
    mem->Data[i] = 0;  
  }
}
