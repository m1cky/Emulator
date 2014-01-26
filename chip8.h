#include <string>
#include <SDL.h>
#include <SDL_image.h>

// Current upcode, 2 bytes long
unsigned short opcode;

// 4K memory
unsigned char memory[4096];

// 8 bit registers, V0 through VE. 16th register is CF
unsigned char V[16];

// Index register
unsigned short I;

// Program counter
unsigned short pc;

// Screen - 2048 pixels that are black or white. Values - 0 or 1
unsigned char gfx[64 * 32];

// Hardware timers [60 Hz] that count down to 0 when they are above 0
unsigned char delay_timer;
unsigned char sound_timer; /* System buzzer sounds at 0 */

// Implement a stack with 16 levels and stack pointer
unsigned short stack[16];
unsigned short sp;

// Hex-based keypad (0x0 - 0xF)
unsigned char key[16];

class chip8
{
 private:
 public:
  initialize();
};
