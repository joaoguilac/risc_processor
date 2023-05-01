#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(register_pipeline_1)
{
    sc_in<sc_int<32>> instruction_in;
    sc_out<sc_int<32>> instruction_out;

    sc_clock clk("clk", 10, SC_NS, 0.5);

    // methods
    void pass_instruction();

    SC_CTOR(register_pipeline_1)
    {
        SC_METHOD(pass_instruction);
        sensitive << clk;
    }
};

void register_pipeline_1::pass_instruction()
{
    instruction_out.write(instruction_in);
}