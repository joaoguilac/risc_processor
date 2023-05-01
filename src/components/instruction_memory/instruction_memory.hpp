#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(instruction_memory)
{
    sc_in<sc_uint<5>> address;
    sc_clock clk("clk", 10, SC_NS, 0.5);
    sc_out<sc_int<32>> instruction_out;

    sc_vector<sc_int<32>> instruction_bank[32];

    // methods
    void next_instruction();

    SC_CTOR(instruction_memory)
    {
        SC_METHOD(next_instruction);
        sensitive << clk;
    }
};

void instruction_memory::next_instruction()
{
    instruction_out.write(instruction_bank[address.read()]);
}