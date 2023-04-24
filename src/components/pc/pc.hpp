#include "systemc.h"

SC_MODULE(pc) {
    sc_in<sc_uint> jump_position;
    sc_in<bool> Jump, Reset;
    sc_clock clk("clk", 10, SC_NS, 0.5);
    sc_out<sc_uint> instruction_position;

    sc_int counter = 0;

    // methods
    void next_instruction();

    SC_CTOR(pc) {
        SC_METHOD(next_instruction);
        sensitive << Reset << clk;
    }
}

void pc::next_instruction() {
    if (Reset.read()) {
        counter = 0;
    }
    else {
        if (Jump.read()) {
            counter = jump_position.read();
        }
        else {
            counter++;
        }
    }
    instruction_position.write(counter);
}