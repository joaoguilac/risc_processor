#include "systemc.h"
#include "control/control.hpp"
#include "data_memory/data_memory.hpp"
#include "instruction_memory/instruction_memory.hpp"
#include "mux/mux32.hpp"
#include "mux/mux5.hpp"
#include "pc/pc.hpp"
#include "registers/registers.hpp"
#include "registers_pipeline/register_pipeline_1.hpp"
#include "registers_pipeline/register_pipeline_2.hpp"
#include "registers_pipeline/register_pipeline_3.hpp"
#include "registers_pipeline/register_pipeline_4.hpp"
#include "ula/ula.hpp"

SC_MODULE(processor)
{
    //=== Components
    ula Ula{"Ula"};
    registers Register{"Register"};
    register_pipeline_1 RegPipeline1{"RegPipeline1"};
    register_pipeline_2 RegPipeline2{"RegPipeline2"};
    register_pipeline_3 RegPipeline3{"RegPipeline3"};
    register_pipeline_4 RegPipeline4{"RegPipeline4"};
    pc PC{"PC"};
    mux5 MuxUla1{"MuxUla1"};
    mux32 MuxUla2{"MuxUla2"};
    mux32 MuxData{"MuxData"};
    instruction_memory InstMemory{"InstMemory"};
    data_memory DataMemory{"DataMemory"};
    control Control{"Control"};

    //=== Signals
    // PC
    sc_signal<bool> JumpCmpPC;
    sc_signal<sc_uint<5>> JumpPositionPC; // IN
    sc_signal<sc_uint<5>> InstructionAddresPC;

    // Instruction Memory
    sc_signal<sc_int<32>> InstructionOutInstMemory;

    // Register Pipeline 1
    sc_signal<sc_int<32>> InstructionOutPipe1;

    // Register Bank
    sc_signal<sc_int<32>> DataOut1RegisterBank, DataOut2RegisterBank;

    // Register Pipeline 2
    sc_signal<sc_int<32>> InstructionOutPipe2, DataOut1Pipe2, DataOut2Pipe2;
    sc_signal<sc_int<5>> AddrMemLoadFonteOutPipe2, AddrIlaRegOutPipe2, AddrMemLoadRegOutPipe2, AddrMemWriteOutPipe2;
    sc_signal<bool> UlaOPOutPipe2, CtrlMemWriteOutPipe2, JumpOutPipe2, RegWriteOutPipe2, MemLoadOutPipe2, JumpCmpOutPipe2, JumpNegOutPipe2;

    // Ula
    sc_signal<bool> JumpResultUla;
    sc_signal<sc_int<32>> DataOutUla;

    // Mux 5
    sc_signal<sc_int<5>> OutMux5;

    // Mux 32 1
    sc_signal<sc_int<32>> Out1Mux32;

    // Register Pipeline 3
    sc_signal<sc_int<32>> InstructionOutPipe3, DataMuxOutPipe3;
    sc_signal<sc_int<5>> AddrMemLoadFonteOutPipe3, AddrMuxRegOutPipe3, AddrMemWriteOutPipe3;
    sc_signal<bool> JumpResultOutPipe3;
    sc_signal<bool> CtrlMemWriteOutPipe3, JumpOutPipe3, RegWriteOutPipe3, MemLoadOutPipe3, JumpCmpOutPipe3;

    // Data Memory
    sc_signal<sc_int<32>> DataLoadOutDataMemory;

    // Register Pipeline 4
    sc_signal<sc_int<32>> DataUlaOutPipe4, DataMemOutPipe4;
    sc_signal<sc_int<5>> AddrMuxRegOutPipe4;
    sc_signal<bool> RegWriteOutPipe4, MemLoadOutPipe4;

    // Mux 32 2
    sc_signal<sc_int<32>> Out2Mux32;

    //=== Methods

    SC_CTOR(processor)
    {
        sc_bv<32> Aux32BitVector;
        sc_bv<5> Aux5BitVector;
        sc_int<32> Aux32Int;
        sc_int<5> Aux5Int;
        sc_uint<5> Aux5Uint;

        // PC
        Aux32BitVector = InstructionOutPipe2;
        Aux5BitVector = Aux32BitVector.range(25, 21);
        Aux5Uint = Aux5BitVector.to_uint();
        JumpPositionPC = Aux5Uint;
        //// IN
        PC.JumpPosition(JumpPositionPC);
        PC.Jump(JumpOutPipe3);

        JumpCmpPC = JumpResultOutPipe3 & JumpCmpOutPipe3;
        PC.JumpCmp(JumpCmpPC);
        //// Out
        PC.InstructionAddres(InstructionAddresPC);

        // Instruction Memory

        // Register Pipeline 1

        // Register Bank

        // Register Pipeline 2

        // Ula

        // Mux 5

        // Mux 32

        // Register Pipeline 3

        // Data Memory

        // Register Pipeline 4

        // Mux 32
    }
};