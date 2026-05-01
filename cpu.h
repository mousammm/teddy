#pragma once
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
  u8 a; /* accumulator */
  u8 x; /* index */
  u8 y; /* index */
  u16 pc; /* program counter */
} CPU;

static CPU cpu = { 0x00, 0x00, 0x00, 0x1000 };
static u8 RAM[0x10000] = {0};
