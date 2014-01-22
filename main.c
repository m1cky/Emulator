#include "system.h"

int main()
{
  char* filename = "memory.txt";

  printf("%s", readData(filename, 512, "Micky"));
  
  return 0;
}
