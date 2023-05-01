#include "systemc.h"

SC_MODULE(pc)
{
    sc_in<sc_uint<5>> jump_position;
    sc_in<bool> Jump, JumpCmp, Reset;
    sc_clock clk("clk", 10, SC_NS, 0.5);
    sc_out<sc_uint<5>> instruction_address;

    sc_uint<5> counter = 0;

    // methods
    void next_instruction();

    SC_CTOR(pc)
    {
        SC_METHOD(next_instruction);
        sensitive << Reset << clk;
    }
};

void pc::next_instruction()
{
    if (Reset.read())
    {
        counter = 0;
    }
    else
    {
        if (Jump.read() || JumpCmp.read())
        {
            counter = jump_position.read();
        }
        else
        {
            counter++;
        }
    }
    instruction_address.write(counter);
}