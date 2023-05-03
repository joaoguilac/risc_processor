#include "systemc.h"

SC_MODULE(ula)
{
    sc_in<sc_int<32>> op1, op2;
    sc_in<sc_uint<3>> UlaInst;
    sc_in<sc_uint<1>> UlaOP, JumpCmp, JumpNeg;
    sc_out<sc_uint<1>> jump_result;
    sc_out<sc_int<32>> out_data;

    // methods
    void execute();

    SC_CTOR(ula)
    {
        SC_METHOD(execute);
        sensitive << op1 << op2 << UlaInst;
    }
};

void ula::execute()
{
    int op = UlaInst.read();

    switch (op)
    {
    case 1: // And
        out_data.write(op1.read() & op2.read());
        break;
    case 2: // Or
        out_data.write(op1.read() | op2.read());
        break;
    case 3: // Xor
        out_data.write(op1.read() ^ op2.read());
        break;
    case 4: // Not
        out_data.write(~op1.read());
        break;
    case 5: // Cmp
        if (JumpCmp.read())
            if (JumpNeg.read())
            {
                if (op1.read() < 0)
                    jump_result.write(1);
                else
                    jump_result.write(0);
            }
            else
            {
                if (op1.read() == 0)
                    jump_result.write(1);
                else
                    jump_result.write(0);
            }
        else if (op1.read() == op2.read())
        {
            out_data.write(1);
        }
        else
        {
            out_data.write(0);
        }
        break;
    case 6: // Add
        out_data.write(op1.read() + op2.read());
        break;
    case 7: // Sub
        out_data.write(op1.read() - op2.read());
        break;
    }
}