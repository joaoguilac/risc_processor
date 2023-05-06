#include "systemc.h"
#include "./ula.hpp"
#include "./testbench.hpp"

int sc_main(int argc, char *argv[])
{
    sc_signal<sc_int<32>> ASig, BSig, SSig;
    sc_signal<sc_uint<3>> OpSig;
    sc_clock TestClk("TestClock", 10, SC_NS, 0.5);

    // testbench
    testbench Tb("Stimulus");
    Tb.A(ASig);
    Tb.B(BSig);
    Tb.Op(OpSig);
    Tb.Clk(TestClk);

    // ula
    ula myAlu("ula");
    myAlu.op1(ASig);
    myAlu.op2(BSig);
    myAlu.ALUOp(OpSig);
    myAlu.out(SSig);

    //========================= waveform
    sc_trace_file *fp;
    fp = sc_create_vcd_trace_file("ula");
    fp->set_time_unit(1, sc_core::SC_NS);

    sc_trace(fp, myAlu.op1, "op1");
    sc_trace(fp, myAlu.op2, "op2");
    sc_trace(fp, myAlu.ALUOp, "ALUOp");
    sc_trace(fp, myAlu.out, "out");
    sc_trace(fp, TestClk, "CLK");
    //=========================

    sc_start();

    sc_close_vcd_trace_file(fp);

    return 0;
}