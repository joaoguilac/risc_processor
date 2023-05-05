#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(register_pipeline_1)
{
    sc_in<sc_int<32>> InstructionIn;
    sc_out<sc_int<32>> InstructionOut;

    sc_port<sc_signal_in_if<bool>> clock;

    // methods
    void pass_instruction();

    SC_CTOR(register_pipeline_1)
    {
        SC_METHOD(pass_instruction);
        sensitive << clock.pos();
    }
};

void register_pipeline_1::pass_instruction()
{
    InstructionOut.write(InstructionIn);
}