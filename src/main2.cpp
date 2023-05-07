#include "systemc.h"

#include <vector>
#include <string>
#include <sstream>
#include <fstream>

// MODULES
#include "components/control/control.hpp"
#include "components/data_memory/data_memory.hpp"
#include "components/instruction_memory/instruction_memory.hpp"
#include "components/mux/mux32.hpp"
#include "components/mux/mux5.hpp"
#include "components/pc/pc.hpp"
#include "components/registers_bank/registers_bank.hpp"
#include "components/registers_pipeline/register_pipeline_1.hpp"
#include "components/registers_pipeline/register_pipeline_2.hpp"
#include "components/registers_pipeline/register_pipeline_3.hpp"
#include "components/registers_pipeline/register_pipeline_4.hpp"
#include "components/ula/ula.hpp"
#include "./testbench.hpp"

using namespace std;

int decode(string instruction)
{
    // Faz a decodificação da entrada das instruções
    // Para instruçõs de ULA ela deve vir "Operação" "Registrador Um" "Registrador Dois" "Registrador Destino"
    // Para instruções de Mémoria, ela deve vir como "Operação" "Registrador Fonte" "Registrador Destino"
    // Para instruções de Jump, deve vir como "Operação" "Posição"

    // cout << "Inst: " << instruction << " ";

    int decodedInstruction = 0;
    int tmpInt;

    string tmp;
    stringstream ss(instruction);
    vector<string> words;

    while (getline(ss, tmp, ' '))
    {
        words.push_back(tmp);
    }
    for (auto word : words)
        cout << word << " ";
    cout << "Size " << words.size() << " ";
    if (words.size() == 4) // Ula
    {
        if (words[0] == "AND")
        {
            tmpInt = 1;
        }
        else if (words[0] == "OR")
        {
            tmpInt = 2;
        }
        else if (words[0] == "XOR")
        {
            tmpInt = 3;
        }
        else if (words[0] == "NOT")
        {
            tmpInt = 4;
        }
        else if (words[0] == "CMP")
        {
            tmpInt = 5;
        }
        else if (words[0] == "ADD")
        {
            tmpInt = 6;
        }
        else if (words[0] == "SUB")
        {
            tmpInt = 7;
        }
        decodedInstruction |= (tmpInt << 26);

        decodedInstruction |= (stoi(words[1]) << 21);

        decodedInstruction |= (stoi(words[2]) << 16);

        decodedInstruction |= (stoi(words[3]) << 11);
    }
    else if (words.size() == 3) // Memória
    {
        if (words[0] == "LD")
        {
            tmpInt = 1;
        }
        else if (words[0] == "ST")
        {
            tmpInt = 2;
        }

        decodedInstruction |= (tmpInt << 29);

        decodedInstruction |= (stoi(words[1]) << 21);

        decodedInstruction |= (stoi(words[2]) << 16);
    }
    else if (words.size() == 2) // Jump
    {
        if (words[0] == "J")
        {
            tmpInt = 3;

            decodedInstruction |= (tmpInt << 29);
        }
        else if (words[0] == "JN")
        {
            tmpInt = 37;

            decodedInstruction |= (tmpInt << 26);
        }
        else if (words[0] == "JZ")
        {
            tmpInt = 45;
            decodedInstruction |= (tmpInt << 26);
        }

        decodedInstruction |= (stoi(words[1]) << 21);
    }

    return decodedInstruction;
}

int sc_main(int argc, char *argv[])
{
    //!=== Components ===!//
    ula Ula{"Ula"};
    registers_bank RegistersBank{"RegistersBank"};
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
    testbench TestBench("TestBench");

    //!=== Signals ===!//
    sc_clock clock("clock", 10, SC_NS, 0.5);

    //* PC
    sc_signal<bool> JumpCmpPC;
    sc_signal<sc_uint<5>> InstructionAddresPC;
    sc_signal<sc_uint<5>> JumpPositionPC; // IN

    //* Instruction Memory
    sc_signal<sc_int<32>> InstructionOutInstMemory;

    //* Register Pipeline 1
    sc_signal<sc_int<32>> InstructionOutPipe1;

    //* Control
    sc_signal<bool> ResetControl, JumpCmpControl, MemLoadControl, RegWriteControl, JumpControl, CtrlMemWriteControl, UlaOPControl, RegUlaControl, JumpNegControl;
    sc_signal<sc_uint<3>> OperationControl; // IN

    //* Registers Bank
    sc_signal<sc_int<32>> DataOut1RegisterBank, DataOut2RegisterBank;
    sc_signal<sc_uint<5>> LoadAddress1RegisterBank, LoadAddress2RegisterBank, WriteAddressRegisterBank; // IN

    //* Register Pipeline 2
    sc_signal<sc_int<32>> InstructionOutPipe2, DataOut1Pipe2, DataOut2Pipe2;
    sc_signal<sc_uint<5>> AddrMemLoadFonteOutPipe2, AddrUlaRegOutPipe2, AddrMemLoadRegOutPipe2, AddrMemWriteOutPipe2;
    sc_signal<bool> UlaOPOutPipe2, CtrlMemWriteOutPipe2, JumpOutPipe2, RegWriteOutPipe2, MemLoadOutPipe2, JumpCmpOutPipe2, JumpNegOutPipe2;
    sc_signal<sc_uint<5>> AddrMemLoadFonteInPipe2, AddrUlaRegInPipe2, AddrMemLoadRegInPipe2, AddrMemWriteInPipe2; // IN

    //* Ula
    sc_signal<bool> JumpResultUla;
    sc_signal<sc_int<32>> DataOutUla;
    sc_signal<sc_uint<3>> UlaInstUla; // IN

    //* Mux 5 Ula
    sc_signal<sc_uint<5>> OutMux5;

    //* Mux 32 Ula
    sc_signal<sc_int<32>> Out1Mux32;

    //* Register Pipeline 3
    sc_signal<sc_int<32>> InstructionOutPipe3, DataMuxOutPipe3;
    sc_signal<sc_uint<5>> AddrMemLoadFonteOutPipe3, AddrMuxRegOutPipe3, AddrMemWriteOutPipe3;
    sc_signal<bool> JumpResultOutPipe3;
    sc_signal<bool> CtrlMemWriteOutPipe3, JumpOutPipe3, RegWriteOutPipe3, MemLoadOutPipe3, JumpCmpOutPipe3;

    //* Data Memory
    sc_signal<sc_int<32>> DataLoadOutDataMemory;

    //* Register Pipeline 4
    sc_signal<sc_int<32>> DataUlaOutPipe4, DataMemOutPipe4;
    sc_signal<sc_uint<5>> AddrMuxRegOutPipe4;
    sc_signal<bool> RegWriteOutPipe4, MemLoadOutPipe4;

    //* Mux 32 Reg
    sc_signal<sc_int<32>> Out2Mux32;

    //!=== Dedicated Channels ===!//
    sc_bv<32> Aux32BitVector;
    sc_bv<5> Aux5BitVector;
    sc_bv<3> Aux3BitVector;
    sc_int<32> Aux32Int;
    sc_int<5> Aux5Int;
    sc_int<3> Aux3Int;
    sc_uint<5> Aux5Uint;
    sc_uint<3> Aux3Uint;

    //* PC
    Aux32BitVector = InstructionOutPipe2;
    Aux5BitVector = Aux32BitVector.range(25, 21);
    Aux5Uint = Aux5BitVector.to_uint();
    JumpPositionPC = Aux5Uint;
    //== In
    PC.JumpPosition(JumpPositionPC);
    PC.Jump(JumpOutPipe3);

    JumpCmpPC = JumpResultOutPipe3 & JumpCmpOutPipe3;
    PC.JumpCmp(JumpCmpPC);
    PC.Reset(ResetControl);
    PC.clock(clock);
    //== Out
    PC.InstructionAddres(InstructionAddresPC);

    //* Instruction Memory
    //== In
    InstMemory.Address(InstructionAddresPC);
    InstMemory.clock(clock);
    //== Out
    InstMemory.InstructionOut(InstructionOutInstMemory);

    //* Register Pipeline 1
    //== In
    RegPipeline1.InstructionIn(InstructionOutInstMemory);
    RegPipeline1.clock(clock);
    //== Out
    RegPipeline1.InstructionOut(InstructionOutPipe1);

    //* Control
    //== In
    Aux32Int = InstructionOutPipe1;
    Aux32BitVector = Aux32Int;
    Aux3BitVector = Aux32BitVector.range(28, 26);
    Aux3Uint = Aux3BitVector.to_uint();
    OperationControl = Aux3Uint;
    Control.Operation(OperationControl);
    Control.clock(clock);
    //== Out
    Control.Reset(ResetControl);
    Control.JumpCmp(JumpCmpControl);
    Control.MemLoad(MemLoadControl);
    Control.RegWrite(RegWriteControl);
    Control.Jump(JumpControl);
    Control.CtrlMemWrite(CtrlMemWriteControl);
    Control.UlaOP(UlaOPControl);
    Control.RegUla(RegUlaControl);
    Control.JumpNeg(JumpNegControl);

    //* Registers Bank
    //== In
    Aux32Int = InstructionOutPipe1;
    Aux32BitVector = Aux32Int;

    Aux5BitVector = Aux32BitVector.range(25, 21);
    Aux5Uint = Aux5BitVector.to_uint();
    LoadAddress1RegisterBank = Aux5Uint;
    RegistersBank.LoadAddress1(LoadAddress1RegisterBank);

    Aux5BitVector = Aux32BitVector.range(20, 16);
    Aux5Uint = Aux5BitVector.to_uint();
    LoadAddress2RegisterBank = Aux5Uint;
    RegistersBank.LoadAddress2(LoadAddress2RegisterBank);
    RegistersBank.WriteAddress(AddrMuxRegOutPipe4);
    RegistersBank.WriteData(Out2Mux32);
    RegistersBank.RegWrite(RegWriteOutPipe3);
    RegistersBank.MemWrite(CtrlMemWriteControl);
    RegistersBank.RegUla(RegUlaControl);
    RegistersBank.clock(clock);
    //== Out
    RegistersBank.DataOut1(DataOut1RegisterBank);
    RegistersBank.DataOut2(DataOut2RegisterBank);

    //* Register Pipeline 2
    //== In
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
    RegPipeline2.clock(clock);
    //== Out
    RegPipeline2.InstructionOut(InstructionOutPipe2);
    RegPipeline2.DataOut1(DataOut1Pipe2);
    RegPipeline2.DataOut2(DataOut2Pipe2);
    RegPipeline2.AddrMemLoadFonteOut(AddrMemLoadFonteOutPipe2);
    RegPipeline2.AddrUlaRegOut(AddrUlaRegOutPipe2);
    RegPipeline2.AddrMemLoadRegOut(AddrMemLoadRegOutPipe2);
    RegPipeline2.AddrMemWriteOut(AddrMemWriteOutPipe2);
    RegPipeline2.UlaOPOut(UlaOPOutPipe2);
    RegPipeline2.CtrlMemWriteOut(CtrlMemWriteOutPipe2);
    RegPipeline2.JumpOut(JumpOutPipe2);
    RegPipeline2.RegWriteOut(RegWriteOutPipe2);
    RegPipeline2.MemLoadOut(MemLoadOutPipe2);
    RegPipeline2.JumpCmpOut(JumpCmpOutPipe2);
    RegPipeline2.JumpNegOut(JumpNegOutPipe2);

    //* Ula
    //== In
    Ula.Op1(DataOut1Pipe2);
    Ula.Op2(DataOut2Pipe2);

    Aux32Int = InstructionOutPipe2;
    Aux32BitVector = Aux32Int;
    Aux3BitVector = Aux32BitVector.range(28, 26);
    Aux3Uint = Aux3BitVector.to_uint();
    UlaInstUla = Aux3Uint;
    Ula.UlaInst(UlaInstUla);
    Ula.UlaOP(UlaOPOutPipe2);
    Ula.JumpCmp(JumpCmpOutPipe2);
    Ula.JumpNeg(JumpNegOutPipe2);
    //== Out
    Ula.JumpResult(JumpResultUla);
    Ula.DataOut(DataOutUla);

    //* Mux 5 Ula
    //== In
    MuxUla1.Entry1(AddrUlaRegOutPipe2);
    MuxUla1.Entry2(AddrMemLoadRegOutPipe2);
    MuxUla1.Control(UlaOPControl);
    //== Out
    MuxUla1.Out(OutMux5);

    //* Mux 32 Ula
    //== In
    MuxUla2.Entry1(DataOutUla);
    MuxUla2.Entry2(DataOut1Pipe2);
    MuxUla2.Control(UlaOPControl);
    //== Out
    MuxUla2.Out(Out1Mux32);

    //* Register Pipeline 3
    //== In
    RegPipeline3.InstructionIn(InstructionOutPipe2);
    RegPipeline3.DataMuxIn(Out1Mux32);
    RegPipeline3.AddrMemLoadFonteIn(AddrMemLoadFonteOutPipe2);
    RegPipeline3.AddrMuxRegIn(OutMux5);
    RegPipeline3.AddrMemWriteIn(AddrMemWriteOutPipe2);
    RegPipeline3.JumpResultIn(JumpResultUla);
    RegPipeline3.CtrlMemWriteIn(CtrlMemWriteOutPipe2);
    RegPipeline3.JumpIn(JumpOutPipe2);
    RegPipeline3.RegWriteIn(RegWriteOutPipe2);
    RegPipeline3.MemLoadIn(MemLoadOutPipe2);
    RegPipeline3.JumpCmpIn(JumpCmpOutPipe2);
    RegPipeline3.clock(clock);
    //== Out
    RegPipeline3.InstructionOut(InstructionOutPipe3);
    RegPipeline3.DataMuxOut(DataMuxOutPipe3);
    RegPipeline3.AddrMemLoadFonteOut(AddrMemLoadFonteOutPipe3);
    RegPipeline3.AddrMuxRegOut(AddrMuxRegOutPipe3);
    RegPipeline3.AddrMemWriteOut(AddrMemWriteOutPipe3);
    RegPipeline3.JumpResultOut(JumpResultOutPipe3);
    RegPipeline3.CtrlMemWriteOut(CtrlMemWriteOutPipe3);
    RegPipeline3.JumpOut(JumpOutPipe3);
    RegPipeline3.RegWriteOut(RegWriteOutPipe3);
    RegPipeline3.MemLoadOut(MemLoadOutPipe3);
    RegPipeline3.JumpCmpOut(JumpCmpOutPipe3);

    //* Data Memory
    //== In
    DataMemory.AddresLoad(AddrMemLoadFonteOutPipe3);
    DataMemory.AddresWrite(AddrMemWriteOutPipe3);
    DataMemory.DataWriteIn(DataMuxOutPipe3);
    DataMemory.MemWrite(CtrlMemWriteOutPipe3);
    DataMemory.MemLoad(MemLoadOutPipe3);
    DataMemory.clock(clock);
    //== Out
    DataMemory.DataLoadOut(DataLoadOutDataMemory);

    //* Register Pipeline 4
    //== In
    RegPipeline4.DataUlaIn(DataMuxOutPipe3);
    RegPipeline4.DataMemIn(DataLoadOutDataMemory);
    RegPipeline4.AddrMuxRegIn(AddrMuxRegOutPipe3);
    RegPipeline4.RegWriteIn(RegWriteOutPipe3);
    RegPipeline4.MemLoadIn(MemLoadOutPipe3);
    RegPipeline4.clock(clock);
    //== Out
    RegPipeline4.DataUlaOut(DataUlaOutPipe4);
    RegPipeline4.DataMemOut(DataMemOutPipe4);
    RegPipeline4.AddrMuxRegOut(AddrMuxRegOutPipe4);
    RegPipeline4.RegWriteOut(RegWriteOutPipe4);
    RegPipeline4.MemLoadOut(MemLoadOutPipe4);

    //* Mux 32 Reg
    //== In
    MuxData.Entry1(DataMemOutPipe4);
    MuxData.Entry2(DataUlaOutPipe4);
    MuxData.Control(MemLoadOutPipe3);
    //== Out
    MuxData.Out(Out2Mux32);

    //* Testbench
    TestBench.clock(clock);

    //!=== Read file ===!//
    fstream fileData;
    sc_int<32> dataMem[32]; // Vetor com dados para entrarem na memória de dados
    fileData.open("../data/data_memory.dat");
    if (!fileData)
    {
        cout << "Erro no carregamento do arquivo de dados";
        exit(1);
    }

    int data, i{0};
    while (fileData >> data)
    {
        DataMemory.MemoryBank[i] = data;
        i++;
    }

    fstream fileInstruction;
    sc_int<32> instructionMem[32]; // Vetor com dados para entrarem na memória de instruções
    string fileName = argv[1];
    fileInstruction.open(fileName);
    if (!fileInstruction)
    {
        cout << "Erro no carregamento do arquivo de instruções";
        exit(1);
    }
    string instStr;
    int instInt;
    i = 0;
    while (getline(fileInstruction, instStr))
    {
        instInt = decode(instStr);
        InstMemory.InstructionBank[i] = instInt;
        cout << "Code " << InstMemory.InstructionBank[i] << endl;
        i++;
    }

    //!=== Waveform ===!//
    sc_trace_file *fp;
    fp = sc_create_vcd_trace_file("wave");
    fp->set_time_unit(1, sc_core::SC_NS);

    sc_trace(fp, clock, "clock");

    sc_trace(fp, PC.Reset, "PCReset");
    sc_trace(fp, PC.JumpCmp, "PCJumpCmp");
    sc_trace(fp, PC.Jump, "PCJump");
    sc_trace(fp, PC.counter, "PCcounter");
    sc_trace(fp, PC.InstructionAddres, "PCInstruction");
    sc_trace(fp, InstMemory.Address, "InstMemAddress");
    sc_trace(fp, InstMemory.InstructionOut, "InstMemInstOut");
    sc_trace(fp, RegPipeline1.InstructionIn, "RegPip1InstIn");
    sc_trace(fp, RegPipeline1.InstructionOut, "RegPip1InstOut");
    sc_trace(fp, RegistersBank.LoadAddress1, "LoadAddress1");
    sc_trace(fp, RegistersBank.LoadAddress2, "LoadAddress2");
    sc_trace(fp, RegistersBank.WriteAddress, "WriteAddress");
    sc_trace(fp, RegistersBank.WriteData, "WriteData");
    sc_trace(fp, RegistersBank.RegWrite, "RegWrite");
    sc_trace(fp, RegistersBank.MemWrite, "MemWrite");
    sc_trace(fp, RegistersBank.RegUla, "RegUla");
    sc_trace(fp, RegistersBank.DataOut1, "registerDataOut2");
    sc_trace(fp, RegistersBank.DataOut2, "registerDataOut2");
    sc_trace(fp, DataMemory.DataWriteIn, "DataWriteIn");
    sc_trace(fp, Ula.Op1, "UlaOp1");
    sc_trace(fp, Ula.Op2, "UlaOp2");
    sc_trace(fp, Ula.UlaInst, "UlaInst");
    sc_trace(fp, Ula.DataOut, "UlaDataOut");

    sc_start();

    sc_close_vcd_trace_file(fp);

    return 0;
}