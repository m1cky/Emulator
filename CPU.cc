#include <iostream>
#include <string>
#include <cstring>
#include <vector>

typedef unsigned char byte;

namespace Emulator
{
  class CPU
  {
  public:

    static const byte MAX = 255;

    enum InstructionSet
    {
      PUSH0 = 0,
      PUSH1,
      ADD,
      SUB,
      STORE0,
      STORE1
    };
    
  private:
    byte R0, R1;
    bool SF, OF, UF;
    byte PC, I;

    int Temp;

    CPU(const CPU&){};

    void Reset()
    {
      Temp = 0;

      R0 = 0;
      R1 = 0;
      SF = true;
      OF = false;
      UF = false;
      PC = 0;
    }

    void Fault()
    {
      SF = false;
      std::cout << "Instruction fault at: " << PC << std::endl;
      DumpRegs();
    }

    void DumpRegs()
    {
      std::cout << "CPU Registers: " << std::endl
		<< "Register0 [" << R0 << "]" << std::endl
		<< "Register1 [" << R1 << "]" << std::endl
		<< "Status [" << SF << "]" << std::endl
		<< "Overflow [" << OF << "]" << std::endl
		<< "Underflow [" << UF << "]" << std::endl
    		<< "Program Counter [" << PC << "]" << std::endl
		<< "Instruction Register [" << I << "]" << std::endl
		<< "Temp [" << Temp << "]" << std::endl;
    }

    void Push0(const std::vector<byte>& Program)
    {
      R0 = Program[PC];
      PC++;
    }
    void Push1(const std::vector<byte>& Program)
    {
      R1 = Program[PC];
      PC++;
    }
    void Add()
    {
      Temp = R0 + R1;

      if(Temp > MAX)
	{
	  OF = true;
	  Temp = MAX;
	}
      R0 = Temp;
    }
    void Sub()
    {
      Temp = R0 - R1;

      if(Temp < 0)
	{
	  UF = true;
	  Temp = 0;
	}
      R0 = Temp;
    }
    void Store0(std::vector<byte>& Program)
    {
      Program[PC] = R0;
      PC++;
    }
    void Store1(std::vector<byte>& Program)
    {
      Program[PC] = R1;
      PC++;
    }

  public:
    CPU(){ Reset(); }
    ~CPU() {};

    void Execute(std::vector<byte>& Program, const bool& HaltOF = true, const bool& HaltUF = true)
    {
      Reset();

      if(Program.size() > MAX)
	{
	  std::cout << "Error: Unable to process program. Instructions exceed 255" << std::endl;
	}
      else
	{
	  while(PC < Program.size())
	    {
	      I = Program[PC];
	      PC++;

	      switch(I)
		{
		case PUSH0:
		  Push0(Program);
		  break;
		case PUSH1:
		  Push1(Program);
		  break;
		case ADD:
		  Add();
		  break;
		case SUB:
		  Sub();
		  break;
		case STORE0:
		  Store0(Program);
		  break;
		case STORE1:
		  Store1(Program);
		  break;
		default:
		  Fault();
		  return;
		}

	      if(UF && HaltUF)
		{
		  std::cout << "Underflow - Halt" << std::endl;
		  return;
		}
	    }
	}
    }

  };
}

int main(int argc, char* args[])
{
  Emulator::CPU* cpu = new Emulator::CPU();

  std::vector<byte> inst;
  
  inst.push_back(Emulator::CPU::PUSH0);
  inst.push_back(0);
  inst.push_back(Emulator::CPU::PUSH1);
  inst.push_back(7);
  inst.push_back(Emulator::CPU::ADD);
  inst.push_back(Emulator::CPU::STORE0);
  inst.push_back(255);
  std::cout << "CPU & Instructions Ready" << std::endl;

  cpu->Execute(inst);

  std::vector<byte>::const_iterator itr = inst.begin();
  for(; itr != inst.end(); itr++)
    {
      std::cout << "[" << static_cast<int>((*itr)) << "]" << std::endl;
    }

  delete cpu;
  
  return 0;
}
