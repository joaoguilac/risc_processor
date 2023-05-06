#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(instruction_memory)
{
    sc_in<sc_uint<5>> Address;
<<<<<<< HEAD
    sc_in_clk clk;
=======
    sc_in_clk clock;

>>>>>>> e9dc2eba11540e8ca8925d29442cb6e5eb41da65
    sc_out<sc_int<32>> InstructionOut;

    sc_vector<sc_int<32>> InstructionBank[32];

    // methods
    void next_instruction();

    SC_CTOR(instruction_memory)
    {
        SC_METHOD(next_instruction);
<<<<<<< HEAD
        sensitive << clk.pos().pos();
=======
        sensitive << clock.pos();
>>>>>>> e9dc2eba11540e8ca8925d29442cb6e5eb41da65
    }
};

void instruction_memory::next_instruction()
{
    InstructionOut.write(InstructionBank[Address.read()]);
}