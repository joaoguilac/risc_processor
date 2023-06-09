#include "systemc.h"
// #include "sysc/utils/sc_vector.h"

SC_MODULE(control)
{
    sc_in<sc_uint<32>> Operation;
    sc_in_clk clock;

    sc_out<bool> Reset, JumpCmp, MemLoad, RegWrite, Jump, CtrlMemWrite, UlaOP, RegUla, JumpNeg;

    // methods
    void decode();

    SC_CTOR(control)
    {
        SC_METHOD(decode);
        sensitive << Operation;
    }
};

void control::decode()
{
    switch (Operation.read().range(31, 29))
    {
    case 1: // ULA
        Jump.write(0);
        Reset.write(0);
        RegUla.write(1);
        RegWrite.write(1);
        UlaOP.write(1);
        CtrlMemWrite.write(0);
        MemLoad.write(0);
        JumpCmp.write(0);
        JumpNeg.write(0);
        break;
    case 2: // Load
        Jump.write(0);
        Reset.write(0);
        RegUla.write(0);
        RegWrite.write(1);
        UlaOP.write(0);
        CtrlMemWrite.write(0);
        MemLoad.write(1);
        JumpCmp.write(0);
        JumpNeg.write(0);
        break;
    case 3: // Store
        Jump.write(0);
        Reset.write(0);
        RegUla.write(0);
        RegWrite.write(0);
        UlaOP.write(0);
        CtrlMemWrite.write(1);
        MemLoad.write(0);
        JumpCmp.write(0);
        JumpNeg.write(0);
        break;
    case 4: // Jump Absoluto
        Jump.write(1);
        Reset.write(0);
        RegUla.write(0);
        RegWrite.write(0);
        UlaOP.write(0);
        CtrlMemWrite.write(0);
        MemLoad.write(0);
        JumpCmp.write(0);
        JumpNeg.write(0);
        break;
    case 5: // Jump se Negativo
        Jump.write(0);
        Reset.write(0);
        RegUla.write(0);
        RegWrite.write(0);
        UlaOP.write(1);
        CtrlMemWrite.write(0);
        MemLoad.write(0);
        JumpCmp.write(1);
        JumpNeg.write(1);
        break;
    case 6: // Jump se zero
        Jump.write(0);
        Reset.write(0);
        RegUla.write(0);
        RegWrite.write(0);
        UlaOP.write(1);
        CtrlMemWrite.write(0);
        MemLoad.write(0);
        JumpCmp.write(1);
        JumpNeg.write(0);
        break;
    default:
        Jump.write(0);
        Reset.write(0);
        RegUla.write(0);
        RegWrite.write(0);
        UlaOP.write(0);
        CtrlMemWrite.write(0);
        MemLoad.write(0);
        JumpCmp.write(0);
        JumpNeg.write(0);
        break;
    }
}