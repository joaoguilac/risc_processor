#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(register_pipeline_3)
{
    sc_in<sc_uint<32>> InstructionIn, DataMuxIn;
    sc_in<sc_uint<5>> AddrMemLoadFonteIn, AddrMuxRegIn, AddrMemWriteIn;
    sc_in<bool> JumpResultIn;
    sc_in<bool> CtrlMemWriteIn, JumpIn, RegWriteIn, MemLoadIn, JumpCmpIn;
    sc_in_clk clock;

    sc_out<sc_uint<32>> InstructionOut, DataMuxOut;
    sc_out<sc_uint<5>> AddrMemLoadFonteOut, AddrMuxRegOut, AddrMemWriteOut;
    sc_out<bool> JumpResultOut;
    sc_out<bool> CtrlMemWriteOut, JumpOut, RegWriteOut, MemLoadOut, JumpCmpOut;

    // methods
    void pass_instruction();

    SC_CTOR(register_pipeline_3)
    {
        SC_METHOD(pass_instruction);
        sensitive << clock.pos();
    }
};

void register_pipeline_3::pass_instruction()
{
    // std::cout << "Pipe 3 Inst: " << InstructionIn.read() << " ";

    InstructionOut.write(InstructionIn.read());
    DataMuxOut.write(DataMuxIn.read());
    AddrMemLoadFonteOut.write(AddrMemLoadFonteIn.read());
    AddrMuxRegOut.write(AddrMuxRegIn.read());
    AddrMemWriteOut.write(AddrMemWriteIn.read());

    CtrlMemWriteOut.write(CtrlMemWriteIn.read());
    JumpOut.write(JumpIn.read());
    RegWriteOut.write(RegWriteIn.read());
    MemLoadOut.write(MemLoadIn.read());
    JumpCmpOut.write(JumpCmpIn.read());
    JumpResultOut.write(JumpResultIn.read());
}