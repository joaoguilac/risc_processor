#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(controler)
{
    sc_in<sc_uint<3>> operation;
    sc_clock clk("clk", 10, SC_NS, 0.5);
    sc_out<sc_uint<1>> reset, jumpCmp, memLoad, regWrite, jump, ctrlMemWrite, ulaOP, regUla;

    // methods
    void decode();

    SC_CTOR(controler)
    {
        SC_METHOD(decode);
        sensitive << clk;
    }
};

void controler::decode()
{
    switch (operation.read())
    {
    case 0:
        jump.write(0);
        reset.write(0);
        regUla.write(1);
        regWrite.write(1);
        ulaOP.write(1);
        ctrlMemWrite.write(0);
        memLoad.write(0);
        jumpCmp.write(0);
        break;
    case 1:
        jump.write(0);
        reset.write(0);
        regUla.write(0);
        regWrite.write(1);
        ulaOP.write(0);
        ctrlMemWrite.write(0);
        memLoad.write(1);
        jumpCmp.write(0);
        break;
    case 2:
        jump.write(0);
        reset.write(0);
        regUla.write(0);
        regWrite.write(0);
        ulaOP.write(0);
        ctrlMemWrite.write(1);
        memLoad.write(0);
        jumpCmp.write(0);
        break;
    case 3:
        jump.write(1);
        reset.write(0);
        regUla.write(0);
        regWrite.write(0);
        ulaOP.write(0);
        ctrlMemWrite.write(0);
        memLoad.write(0);
        jumpCmp.write(0);
        break;
    case 4:
        jump.write(0);
        reset.write(0);
        regUla.write(0);
        regWrite.write(0);
        ulaOP.write(1);
        ctrlMemWrite.write(0);
        memLoad.write(0);
        jumpCmp.write(1);
        break;
    case 5:
        jump.write(0);
        reset.write(0);
        regUla.write(0);
        regWrite.write(0);
        ulaOP.write(1);
        ctrlMemWrite.write(0);
        memLoad.write(0);
        jumpCmp.write(1);
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
        break;
    }
}