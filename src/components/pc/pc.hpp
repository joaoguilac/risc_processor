#include "systemc.h"

SC_MODULE(pc)
{
    sc_in<sc_int<32>> JumpPosition;
    sc_in<bool> Jump, JumpCmp, Reset;
    sc_in_clk clock;

    sc_out<sc_int<5>> InstructionAddres;

    sc_int<5> counter = -1;

    // methods
    void next_instruction();

    SC_CTOR(pc)
    {
        SC_METHOD(next_instruction);
        sensitive << Reset << clock.pos();
    }
};

void pc::next_instruction()
{
    if (Reset.read())
    {
        counter = -1;
    }
    else
    {
        if (Jump.read() || JumpCmp.read())
        {
            counter = JumpPosition.read().range(25, 21);
        }
        else
        {
            counter++;
        }
    }
    InstructionAddres.write(counter);
}