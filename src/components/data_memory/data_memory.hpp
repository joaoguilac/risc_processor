#include "systemc.h"

SC_MODULE(data_memory) {
    // TODO in/out
    sc_in<sc_uint<4>> address_ula, address_load, address_write;
    sc_in<sc_int<32>> result_ula;
    sc_in<bool> MemWrite;
    sc_out<>

    // TODO methods

    SC_CTOR(data_memory) {
        // TODO constructor
    }
}