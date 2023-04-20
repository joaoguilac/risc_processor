#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(banco_registradores) {
    sc_in<sc_int<16>> address, data;
    sc_in<sc_uint<1>> RegWrite, Enable;
    sc_clock clk()
    sc_out<sc_int<16>> out;

    sc_vector<sc_int<16>> registrador[16];

    void load() {
        out.write(registrador[address.read()]);
    }

    void store() {
        registrador[address.read()].write(data.read());
    }

    void control() {
        if(Enable) {
            if (RegWrite) {
                load();
            }
            else {
                store();
            }
        }
    }

    SC_CTOR(banco_registradores) {
        SC_METHOD(control);
        sensitive << clk;
    }

};
