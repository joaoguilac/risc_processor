#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(register_pipeline_2)
{
    sc_in<sc_int<32>> instruction_in, data_out1_in, data_out2_in;
    sc_in<sc_int<5>> addr_mem_load_fonte_in, addr_ula_reg_in, addr_mem_load_reg_in, addr_mem_write_in;
    sc_in<bool> UlaOPIn, CtrlMemWriteIn, JumpIn, RegWriteIn, MemLoadIn, JumpCmpIn, JumpNegIn;

    sc_out<sc_int<32>> instruction_out, data_out1_out, data_out2_out;
    sc_out<sc_int<5>> addr_mem_load_fonte_out, addr_ula_reg_out, addr_mem_load_reg_out, addr_mem_write_out;
    sc_out<bool> ulaOP_out, ctrlMemWrite_out, jump_out, regWrite_out, memLoad_out, jumpCmp_out, jumpNeg_out;

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
    instruction_out.write(instruction_in.read());
    data_out1_out.write(data_out1_in.read());
    data_out2_out.write(data_out2_in.read());
    addr_mem_load_fonte_out.write(addr_mem_load_fonte_in.read());
    addr_ula_reg_out.write(addr_ula_reg_in.read());
    addr_mem_load_reg_out.write(addr_mem_load_reg_in.read());
    addr_mem_write_out.write(addr_mem_write_in.read());

    ulaOP_out.write(UlaOPIn.read());
    ctrlMemWrite_out.write(CtrlMemWriteIn.read());
    jump_out.write(JumpIn.read());
    regWrite_out.write(RegWriteIn.read());
    memLoad_out.write(MemLoadIn.read());
    jumpCmp_out.write(JumpCmpIn.read());
    jumpNeg_out.write(JumpNegIn.read());
}