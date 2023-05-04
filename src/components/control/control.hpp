#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(control)
{
    sc_in<sc_uint<3>> operation;
    sc_clock clk("clk", 10, SC_NS, 0.5);
    sc_out<bool> reset, jumpCmp, memLoad, regWrite, jump, ctrlMemWrite, ulaOP, regUla, jumpNeg;

    // methods
    void decode();

    SC_CTOR(control)
    {
        SC_METHOD(decode);
        sensitive << clk;
    }
};

void control::decode()
{
    switch (operation.read())
    {
    case 0: // ULA
        jump.write(0);
        reset.write(0);
        regUla.write(1);
        regWrite.write(1);
        ulaOP.write(1);
        ctrlMemWrite.write(0);
        memLoad.write(0);
        jumpCmp.write(0);
        jumpNeg.write(0);
        break;
    case 1: // Load
        jump.write(0);
        reset.write(0);
        regUla.write(0);
        regWrite.write(1);
        ulaOP.write(0);
        ctrlMemWrite.write(0);
        memLoad.write(1);
        jumpCmp.write(0);
        jumpNeg.write(0);
        break;
    case 2: // Store
        jump.write(0);
        reset.write(0);
        regUla.write(0);
        regWrite.write(0);
        ulaOP.write(0);
        ctrlMemWrite.write(1);
        memLoad.write(0);
        jumpCmp.write(0);
        jumpNeg.write(0);
        break;
    case 3: // Jump Absoluto
        jump.write(1);
        reset.write(0);
        regUla.write(0);
        regWrite.write(0);
        ulaOP.write(0);
        ctrlMemWrite.write(0);
        memLoad.write(0);
        jumpCmp.write(0);
        jumpNeg.write(0);
        break;
    case 4: // Jump se Negativo
        jump.write(0);
        reset.write(0);
        regUla.write(0);
        regWrite.write(0);
        ulaOP.write(1);
        ctrlMemWrite.write(0);
        memLoad.write(0);
        jumpCmp.write(1);
        jumpNeg.write(1);
        break;
    case 5: // Jump se zero
        jump.write(0);
        reset.write(0);
        regUla.write(0);
        regWrite.write(0);
        ulaOP.write(1);
        ctrlMemWrite.write(0);
        memLoad.write(0);
        jumpCmp.write(1);
        jumpNeg.write(0);
        break;
    default:
        jump.write(0);
        reset.write(0);
        regUla.write(0);
        regWrite.write(0);
        ulaOP.write(0);
        ctrlMemWrite.write(0);
        memLoad.write(0);
        jumpCmp.write(0);
        jumpNeg.write(0);
        break;
    }
}