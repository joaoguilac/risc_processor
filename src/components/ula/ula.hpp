#include "systemc.h"

SC_MODULE(ula) {
    sc_in<sc_int<16>> op1, op2;
    sc_in<sc_uint<3>> ALUOp;
    sc_out<sc_int<16>> out;

    // methods
    void execute();

    SC_CTOR(ula) {
        SC_METHOD(execute);
        sensitive << op1 << op2 << ALUOp;
    }
};

void ula::execute() {
    int op = ALUOp.read();

    switch(op) {
        case 1:
            out.write(op1.read() & op2.read());
            break;
        case 2:
            out.write(op1.read() | op2.read());
            break;
        case 3:
            out.write(op1.read() ^ op2.read());
            break;
        case 4:
            out.write(~op1.read());
            break;
        case 5:
            if (op1.read() == op2.read()) {
                out.write(1);
            }
            else {
                out.write(0);
            }
            break;
        case 6:
            out.write(op1.read() + op2.read());
            break;
        case 7:
            out.write(op1.read() - op2.read());
            break;
    }
}