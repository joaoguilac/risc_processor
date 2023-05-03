#include "systemc.h"

SC_MODULE(processor)
{
    //=== Components
    ula Ula("ULA");
    registers Registers("Registers");
    register_pipeline_1 RegPipeline1("RegPipeline1");
    register_pipeline_2 RegPipeline2("RegPipeline2");
    register_pipeline_3 RegPipeline3("RegPipeline3");
    register_pipeline_4 RegPipeline4("RegPipeline4");
    pc PC("PC");
    mux5 MuxUla1("MuxUla1");
    mux32 MuxUla2("MuxUla2");
    mux32 MuxData("MuxData");
    instruction_memory InstMemory("InstMemory");
    data_memory DataMemory("DataMemory");
    control Control("Control");

    //=== Signals
    // PC
    sc_signal<sc_uint<1>> Jump;
    sc_signal<sc_uint<1>> JumpCmp;
    sc_signal<sc_uint<1>> Reset;
    sc_signal<sc_uint<5>> posicao_jump;

    // Instruction Memory
    sc_signal<sc_uint<5>> posicao_inst;

    // Register Pipeline 1
    sc_signal<sc_uint<32>> Instruction;

    // Registers
    sc_signal<sc_uint<1>> RegWrite;
    sc_signal<sc_uint<1>> RegUla;
    sc_signal<sc_uint<1>> CtrlMemWrite;
    sc_signal<sc_int<32>> data_reg;

    // Register Pipeline 2
    sc_signal<sc_uint<1>> JumpNeg;
    sc_signal<sc_uint<1>> JumpCmp;
    sc_signal<sc_uint<1>> MemLoad;
    sc_signal<sc_uint<1>> RegWrite;
    sc_signal<sc_uint<1>> Jump;
    sc_signal<sc_uint<1>> CtrlMemWrite;
    sc_signal<sc_uint<1>> UlaOP;
    sc_signal<sc_int<32>> out1_reg;
    sc_signal<sc_int<32>> out2_reg;

    // Ula


    Control.jumpCmp(JumpCmp);
    RegPipeline2.jumpCmp_in(JumpCmp);

    //=== Methods

    SC_CTOR(processor)
    {
        
    }
};