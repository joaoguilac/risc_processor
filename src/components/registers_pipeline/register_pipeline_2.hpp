#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(register_pipeline_2)
{
    sc_in<sc_int<32>> instruction_in, data_out1_in, data_out2_in;
    sc_in<sc_int<5>> addr_mem_load_fonte_in, addr_ula_reg_in, addr_mem_load_reg_in, addr_mem_write_in;
    sc_in<sc_uint<1>> ulaOP_in, ctrlMemWrite_in, jump_in, regWrite_in, memLoad_in, jumpCmp_in, jumpNeg_in;

    sc_out<sc_int<32>> intstruction_out, data_out1_out, data_out2_out;
    sc_out<sc_int<5>> addr_mem_load_fonte_out, addr_ula_reg_out, addr_mem_load_reg_out, addr_mem_write_out;
    sc_out<sc_uint<1>> ulaOP_out, ctrlMemWrite_out, jump_out, regWrite_out, memLoad_out, jumpCmp_out, jumpNeg_out;

    sc_clock clk("clk", 10, SC_NS, 0.5);

    // methods
    void pass_instruction();

    SC_CTOR(register_pipeline_2)
    {
        SC_METHOD(pass_instruction);
        sensitive << clk;
    }
};

void register_pipeline_2::pass_instruction()
{
    intstruction_out.write(instruction_in.read());
    data_out1_out.write(data_out1_in.read());
    data_out2_out.write(data_out2_in.read());
    addr_mem_load_fonte_out.write(addr_mem_load_fonte_in.read());
    addr_ula_reg_out.write(addr_ula_reg_in.read());
    addr_mem_load_reg_out.write(addr_mem_load_reg_in.read());
    addr_mem_write_out.write(addr_mem_write_in.read());

    ulaOP_out.write(ulaOP_in.read());
    ctrlMemWrite_out.write(ctrlMemWrite_in.read());
    jump_out.write(jump_in.read());
    regWrite_out.write(regWrite_in.read());
    memLoad_out.write(memLoad_in.read());
    jumpCmp_out.write(jumpCmp_in.read());
    jumpNeg_out.write(jumpNeg_in.read());
}