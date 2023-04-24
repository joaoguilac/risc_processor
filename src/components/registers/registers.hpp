#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(registers) {
    sc_in<sc_int<16>> address1, address2, memory_data;
    sc_in<sc_uint<1>> RegWrite, RegEnable, RegUla;
    sc_clock clk("clk", 10, SC_NS, 0.5);
    sc_out<sc_int<16>> data_out1, data_out2;

    sc_vector<sc_int<16>> registers_bank[16];

    // methods
    void control();

    SC_CTOR(registers) {
        SC_METHOD(control);
        sensitive << clk;
    }
};

void registers::control() {
    if (RegEnable) {
        if (RegUla) {
            ula_load();
        }
        else {
            if (RegWrite) {
                memory_load();
            }
            else {
                memory_write();
            }
        }
    }
}

void ula_load() {
    data_out1.write(registers_bank[address1.read()]);
    data_out2.write(registers_bank[address2.read()]);
}

void memory_load() {
    registers_bank[address1.read()].write(memory_data.read());
}

void memory_write() {
    data_out1.write(registers_bank[address1.read()]);
}
