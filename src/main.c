#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h" /* u8 u16 */
#include "cpu.h"


int main(int argc, char *argv[])
{
  struct CPU cpu;
  struct MEM mem;

  CPU_Reset(&cpu);
  MEM_Init(&mem);

  printf("Hello world\n");
  return EXIT_SUCCESS;
}
