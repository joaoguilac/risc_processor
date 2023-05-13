#include "systemc.h"

SC_MODULE(pc)
{
    sc_in<sc_uint<32>> JumpPosition;
    sc_in<bool> Jump, JumpCmp, Reset, JumpResult;
    sc_in_clk clock;

    sc_out<sc_uint<5>> InstructionAddress;

    sc_uint<5> counter = 0;
    int first = 0;

    // methods
    void next_instruction();

    SC_CTOR(pc)
    {
        SC_METHOD(next_instruction);
        sensitive << clock.pos();
    }
};

void pc::next_instruction()
{
    if (Jump.read())
    {
        std::cout << "JumpPosition: " << JumpPosition.read().range(25, 21) << std::endl;
        counter = JumpPosition.read().range(25, 21);
    }
    else if ((JumpCmp.read() & JumpResult.read()))
    {
        std::cout << "JumpPosition: " << JumpPosition.read().range(20, 16) << std::endl;
        counter = JumpPosition.read().range(20, 16);
    }
    else
    {
        if (first == 0)
        {
            first = 1;
        }
        else
        {
            counter++;
        }
    }
    InstructionAddress.write(counter);
}