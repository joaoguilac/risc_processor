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
    sc_signal<sc_uint<5>> InstructionAddresPC;
    sc_signal<sc_uint<5>> JumpPositionPC; // IN

    // Instruction Memory
    sc_signal<sc_int<32>> InstructionOutInstMemory;

    // Register Pipeline 1
    sc_signal<sc_int<32>> InstructionOutPipe1;

    // Control
    sc_signal<bool> ResetControl, JumpCmpControl, MemLoadControl, RegWriteControl, JumpControl, CtrlMemWriteControl, UlaOPControl, RegUlaControl, JumpNegControl;
    sc_signal<sc_uint<3>> OperationControl; // IN

    // Register Bank
    sc_signal<sc_int<32>> DataOut1RegisterBank, DataOut2RegisterBank;
    sc_signal<sc_uint<5>> LoadAddress1RegisterBank, LoadAddress2RegisterBank, WriteAddressRegisterBank; // IN

    // Register Pipeline 2
    sc_signal<sc_int<32>> InstructionOutPipe2, DataOut1Pipe2, DataOut2Pipe2;
    sc_signal<sc_int<5>> AddrMemLoadFonteOutPipe2, AddrIlaRegOutPipe2, AddrMemLoadRegOutPipe2, AddrMemWriteOutPipe2;
    sc_signal<bool> UlaOPOutPipe2, CtrlMemWriteOutPipe2, JumpOutPipe2, RegWriteOutPipe2, MemLoadOutPipe2, JumpCmpOutPipe2, JumpNegOutPipe2;
    sc_signal<sc_uint<5>> AddrMemLoadFonteInPipe2, AddrUlaRegInPipe2, AddrMemLoadRegInPipe2, AddrMemWriteInPipe2; // IN

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
    sc_signal<sc_uint<5>> AddrMuxRegOutPipe4;
    sc_signal<bool> RegWriteOutPipe4, MemLoadOutPipe4;

    // Mux 32 2
    sc_signal<sc_int<32>> Out2Mux32;

    //=== Methods

    SC_CTOR(processor)
    {
        sc_bv<32> Aux32BitVector;
        sc_bv<5> Aux5BitVector;
        sc_bv<3> Aux3BitVector;
        sc_int<32> Aux32Int;
        sc_int<5> Aux5Int;
        sc_int<3> Aux3Int;
        sc_uint<5> Aux5Uint;
        sc_uint<3> Aux3Uint;

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
        //// IN
        InstMemory.Address(InstructionAddresPC);
        //// Out
        InstMemory.InstructionOut(InstructionOutInstMemory);

        // Register Pipeline 1
        //// In
        RegPipeline1.InstructionIn(InstructionOutInstMemory);
        //// Out
        RegPipeline1.InstructionOut(InstructionOutPipe1);

        // Control
        ////In
        Aux32Int = InstructionOutPipe1;
        Aux32BitVector = Aux32Int;
        Aux3BitVector = Aux32BitVector.range(28, 26);
        Aux3Uint = Aux3BitVector.to_uint();
        OperationControl = Aux3Uint;
        Control.Operation(OperationControl);
        ////Out

        // Register Bank
        //// In
        Aux32Int = InstructionOutPipe1;
        Aux32BitVector = Aux32Int;

        Aux5BitVector = Aux32BitVector.range(25, 21);
        Aux5Uint = Aux5BitVector.to_uint();
        LoadAddress1RegisterBank = Aux5Uint;
        Register.LoadAddress1(LoadAddress1RegisterBank);

        Aux5BitVector = Aux32BitVector.range(20, 16);
        Aux5Uint = Aux5BitVector.to_uint();
        LoadAddress2RegisterBank = Aux5Uint;
        Register.LoadAddress2(LoadAddress2RegisterBank);
        Register.WriteAddress(AddrMuxRegOutPipe4);
        Register.WriteData(Out2Mux32);
        Register.RegWrite(RegWriteOutPipe3);
        Register.MemWrite(CtrlMemWriteControl);
        Register.RegUla(RegUlaControl);
        //// Out
        Register.DataOut1(DataOut1RegisterBank);
        Register.DataOut2(DataOut2RegisterBank);

        // Register Pipeline 2
        //// IN
        Aux32Int = InstructionOutPipe1;
        Aux32BitVector = Aux32Int;

        RegPipeline2.InstructionIn(InstructionOutPipe1);
        RegPipeline2.DataOut1In(DataOut1RegisterBank);
        RegPipeline2.DataOut2In(DataOut2RegisterBank);

        Aux5BitVector = Aux32BitVector.range(25, 21);
        Aux5Uint = Aux5BitVector.to_uint();
        AddrMemLoadFonteInPipe2 = Aux5Uint;
        RegPipeline2.AddrMemLoadFonteIn(AddrMemLoadFonteInPipe2);

        Aux5BitVector = Aux32BitVector.range(15, 11);
        Aux5Uint = Aux5BitVector.to_uint();
        AddrUlaRegInPipe2 = Aux5Uint;
        RegPipeline2.AddrUlaRegIn(AddrUlaRegInPipe2);

        Aux5BitVector = Aux32BitVector.range(20, 16);
        Aux5Uint = Aux5BitVector.to_uint();
        AddrMemLoadRegInPipe2 = Aux5Uint;
        RegPipeline2.AddrMemLoadRegIn(AddrMemLoadRegInPipe2);

        Aux5BitVector = Aux32BitVector.range(20, 16);
        Aux5Uint = Aux5BitVector.to_uint();
        AddrMemWriteInPipe2 = Aux5Uint;
        RegPipeline2.AddrMemWriteIn(AddrMemWriteInPipe2);

        RegPipeline2.UlaOPIn(UlaOPControl);
        RegPipeline2.CtrlMemWriteIn(CtrlMemWriteControl);
        RegPipeline2.JumpIn(JumpControl);
        RegPipeline2.RegWriteIn(RegWriteControl);
        RegPipeline2.MemLoadIn(MemLoadControl);
        RegPipeline2.JumpCmpIn(JumpCmpControl);
        RegPipeline2.JumpNegIn(JumpNegControl);
        //// Out

        // Ula

        // Mux 5

        // Mux 32

        // Register Pipeline 3

        // Data Memory

        // Register Pipeline 4

        // Mux 32
    }
};