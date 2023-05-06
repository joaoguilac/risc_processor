#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(register_pipeline_4)
{
    sc_in<sc_int<32>> DataUlaIn, DataMemIn;
    sc_in<sc_uint<5>> AddrMuxRegIn;
    sc_in<bool> RegWriteIn, MemLoadIn;

    sc_out<sc_int<32>> DataUlaOut, DataMemOut;
    sc_out<sc_uint<5>> AddrMuxRegOut;
    sc_out<bool> RegWriteOut, MemLoadOut;

    sc_in_clk clk;

    // methods
    void pass_instruction();

    SC_CTOR(register_pipeline_4)
    {
        SC_METHOD(pass_instruction);
        sensitive << clk.pos();
    }
};

void register_pipeline_4::pass_instruction()
{
    DataUlaOut.write(DataUlaIn.read());
    DataMemOut.write(DataMemIn.read());
    AddrMuxRegOut.write(AddrMuxRegIn.read());

    RegWriteOut.write(RegWriteIn.read());
    MemLoadOut.write(MemLoadIn.read());
}