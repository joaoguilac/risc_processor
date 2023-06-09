#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(register_pipeline_1)
{
    sc_in<sc_uint<32>> InstructionIn;
    sc_in_clk clock;

    sc_out<sc_uint<32>> InstructionOut;

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
    // std::cout << "Pipe 1 Inst: " << InstructionIn.read() << " ";
    InstructionOut.write(InstructionIn.read());
}