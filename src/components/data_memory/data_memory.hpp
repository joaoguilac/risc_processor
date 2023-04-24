#include "systemc.h"

SC_MODULE(data_memory) {
    

    // methods
    void next_instruction();

    SC_CTOR(data_memory) {
        SC_METHOD(next_instruction);
        sensitive << Reset << clk;
    }
}

void pc::next_instruction() {

}