#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(instruction_memory)
{
    sc_in<sc_uint<5>> Address;
    sc_out<sc_int<32>> InstructionOut;

    sc_vector<sc_int<32>> InstructionBank[32];

    sc_port<sc_signal_in_if<bool>> clock;

    // methods
    void next_instruction();

    SC_CTOR(instruction_memory)
    {
        SC_METHOD(next_instruction);
        sensitive << clock.pos();
    }
};

void instruction_memory::next_instruction()
{
    InstructionOut.write(InstructionBank[Address.read()]);
}