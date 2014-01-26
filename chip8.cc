#include "chip8.h"

void chip8::initialize()
{
  pc = 0x200; // Program counter starts at 0x200
  opcode = 0;
  I = 0;
  sp = 0;

  memset(gfx, 0, sizeof(gfx)); // Clear display
  memset(stack, 0, sizeof(stack)); // Clear stack
  memset(V, 0, sizeof(V)); // Clear registers
  memset(memory, 0, sizeof(memory)); // Clear memory
  

  // Load Fontset
  for(int i = 0; i < 80; ++i)
    {
      memory[i] = chip8_fontset[i];
    }
}

void chip8::emulateCycle()
{
  // Fetch byte 1 at pc and byte 2 at pc + 1, and combine into a short
  opcode = memory[pc] << 8 | memory[pc + 1];
}
