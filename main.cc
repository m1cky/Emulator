#include "chip8.h"

chip8 CPU;

int main(int argc, char* args[])
{
  // Init render system and register input callback
  initGraphics();
  initInput();

  // Initialize CPU and load game
  CPU.initialize();
  CPU.loadGame("pong");

  for(;;)
    {
      CPU.emulateCycle();

      // Update if draw flag is set
      if(CPU.drawFlag)
	{
	  drawGraphics();
	}

      // Save key press state
      CPU.setKeys();
    }
  
  
  
  return 0;
}
