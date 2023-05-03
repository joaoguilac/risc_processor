#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(register_pipeline_4)
{
    sc_in<sc_int<32>> data_ula_in, data_mem_in;
    sc_in<sc_int<5>> addr_mux_reg_in;
    sc_in<sc_uint<1>> regWrite_in, memLoad_in;

    sc_out<sc_int<32>> data_ula_out, data_mem_out;
    sc_out<sc_int<5>> addr_mux_reg_out;
    sc_out<sc_uint<1>> regWrite_out, memLoad_out;

    sc_clock clk("clk", 10, SC_NS, 0.5);

    // methods
    void pass_instruction();

    SC_CTOR(register_pipeline_4)
    {
        SC_METHOD(pass_instruction);
        sensitive << clk;
    }
};

void register_pipeline_4::pass_instruction()
{
    data_ula_out.write(data_ula_in.read());
    data_mem_out.write(data_mem_in.read());
    addr_mux_reg_out.write(addr_mux_reg_in.read());

    regWrite_out.write(regWrite_in.read());
    memLoad_out.write(memLoad_in.read());
}