#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(register_pipeline_2)
{
    sc_in<sc_int<32>> InstructionIn, DataOut1In, DataOut2In;
    sc_in<sc_int<32>> AddrMemLoadFonteIn, AddrUlaRegIn, AddrMemLoadRegIn, AddrMemWriteIn;
    sc_in<bool> UlaOPIn, CtrlMemWriteIn, JumpIn, RegWriteIn, MemLoadIn, JumpCmpIn, JumpNegIn;
    sc_in_clk clock;

    sc_out<sc_int<32>> InstructionOut, DataOut1, DataOut2;
    sc_out<sc_int<5>> AddrMemLoadFonteOut, AddrUlaRegOut, AddrMemLoadRegOut, AddrMemWriteOut;
    sc_out<bool> UlaOPOut, CtrlMemWriteOut, JumpOut, RegWriteOut, MemLoadOut, JumpCmpOut, JumpNegOut;

    // methods
    void pass_instruction();

    SC_CTOR(register_pipeline_2)
    {
        SC_METHOD(pass_instruction);
        sensitive << clock.pos();
    }
};

void register_pipeline_2::pass_instruction()
{
    InstructionOut.write(InstructionIn.read());
    DataOut1.write(DataOut1In.read());
    DataOut2.write(DataOut2In.read());
    AddrMemLoadFonteOut.write(AddrMemLoadFonteIn.read().range(25, 21));
    AddrUlaRegOut.write(AddrUlaRegIn.read().range(15, 11));
    AddrMemLoadRegOut.write(AddrMemLoadRegIn.read().range(20, 16));
    AddrMemWriteOut.write(AddrMemWriteIn.read().range(20, 16));

    UlaOPOut.write(UlaOPIn.read());
    CtrlMemWriteOut.write(CtrlMemWriteIn.read());
    JumpOut.write(JumpIn.read());
    RegWriteOut.write(RegWriteIn.read());
    MemLoadOut.write(MemLoadIn.read());
    JumpCmpOut.write(JumpCmpIn.read());
    JumpNegOut.write(JumpNegIn.read());
}