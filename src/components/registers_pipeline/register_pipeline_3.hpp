#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(register_pipeline_3)
{
    sc_in<sc_int<32>> instruction_in, data_mux_in;
    sc_in<sc_int<5>> addr_mem_load_fonte_in, addr_mux_reg_in, addr_mem_write_in;
    sc_in<sc_uint<1>> jumpResult_in;
    sc_in<sc_uint<1>> ctrlMemWrite_in, jump_in, regWrite_in, memLoad_in, jumpCmp_in;

    sc_out<sc_int<32>> intstruction_out, data_mux_out;
    sc_out<sc_int<5>> addr_mem_load_fonte_out, addr_mux_reg_out, addr_mem_write_out;
    sc_out<sc_uint<1>> jumpResult_out;
    sc_out<sc_uint<1>> ctrlMemWrite_out, jump_out, regWrite_out, memLoad_out, jumpCmp_out;

    sc_clock clk("clk", 10, SC_NS, 0.5);

    // methods
    void pass_instruction();

    SC_CTOR(register_pipeline_3)
    {
        SC_METHOD(pass_instruction);
        sensitive << clk;
    }
};

void register_pipeline_3::pass_instruction()
{
    intstruction_out.write(instruction_in.read());
    data_mux_out.write(data_mux_in.read());
    addr_mem_load_fonte_out.write(addr_mem_load_fonte_in.read());
    addr_mux_reg_out.write(addr_mux_reg_in.read());
    addr_mem_write_out.write(addr_mem_write_in.read());

    ctrlMemWrite_out.write(ctrlMemWrite_in.read());
    jump_out.write(jump_in.read());
    regWrite_out.write(regWrite_in.read());
    memLoad_out.write(memLoad_in.read());
    jumpCmp_out.write(jumpCmp_in.read());
}