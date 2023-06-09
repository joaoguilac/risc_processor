#include "systemc.h"
#include "sysc/utils/sc_vector.h"

#include <vector>

SC_MODULE(instruction_memory)
{
    sc_in<sc_uint<5>> Address;

    sc_out<sc_uint<32>> InstructionOut;

    sc_uint<32> InstructionBank[32];

    sc_in_clk clock;

    // methods
    void next_instruction();

    SC_CTOR(instruction_memory)
    {
        SC_METHOD(next_instruction);
        sensitive << Address;
    }
};

void instruction_memory::next_instruction()
{
    InstructionOut.write(InstructionBank[Address.read()]);
}