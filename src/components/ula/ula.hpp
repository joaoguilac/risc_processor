#include "systemc.h"

SC_MODULE(ula)
{
    sc_in<sc_uint<32>> Op1, Op2;
    sc_in<sc_uint<32>> UlaInst;
    sc_in<bool> UlaOP, JumpCmp, JumpNeg;
    sc_in_clk clock;

    sc_out<bool> JumpResult;
    sc_out<sc_uint<32>> DataOut;

    // methods
    void execute();

    SC_CTOR(ula)
    {
        SC_METHOD(execute);
        sensitive << Op1 << Op2 << UlaInst;
    }
};

void ula::execute()
{
    int op = UlaInst.read().range(28, 26);

    switch (op)
    {
    case 1: // And
        DataOut.write(Op1.read() & Op2.read());
        break;
    case 2: // Or
        DataOut.write(Op1.read() | Op2.read());
        break;
    case 3: // Xor
        DataOut.write(Op1.read() ^ Op2.read());
        break;
    case 4: // Not
        DataOut.write(~Op1.read());
        break;
    case 5: // Cmp
        if (JumpCmp.read())
            if (JumpNeg.read())
            {
                if (Op1.read().to_int() < 0)
                    JumpResult.write(1);
                else
                    JumpResult.write(0);
            }
            else
            {
                if (Op1.read() == 0)
                    JumpResult.write(1);
                else
                    JumpResult.write(0);
            }
        else if (Op1.read() == Op2.read())
        {
            DataOut.write(1);
        }
        else
        {
            DataOut.write(0);
        }
        break;
    case 6: // Add
        DataOut.write(Op1.read() + Op2.read());
        break;
    case 7: // Sub
        DataOut.write(Op1.read() - Op2.read());
        break;
    }
}