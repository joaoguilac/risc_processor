#include "systemc.h"
// #include "sysc/utils/sc_vector.h"

#include <vector>

SC_MODULE(registers_bank)
{
    sc_in<sc_uint<32>> LoadAddress1, LoadAddress2;
    sc_in<sc_uint<5>> WriteAddress;
    sc_in<sc_uint<32>> WriteData;
    sc_in<bool> RegWrite, MemWrite, RegUla, JumpCmp;

    sc_out<sc_uint<32>> DataOut1, DataOut2;

    sc_uint<32> RegistersBank[32];

    sc_in_clk clock;

    // methods
    void control();
    void ula_load();
    void memory_load();
    void memory_write();
    void jump_cmp();
    void print();

    SC_CTOR(registers_bank)
    {
        SC_METHOD(control);
        sensitive << LoadAddress1 << LoadAddress2 << WriteAddress << WriteData << RegWrite << MemWrite << RegUla;
    }
};

void registers_bank::control()
{
    if (RegWrite.read())
    {
        memory_load();
    }
    if (RegUla.read())
    {
        ula_load();
    }
    if (MemWrite.read())
    {
        memory_write();
    }
    if (JumpCmp.read())
    {
        jump_cmp();
    }
}

void registers_bank::ula_load()
{
    DataOut1.write(RegistersBank[LoadAddress1.read().range(25, 21)]);
    DataOut2.write(RegistersBank[LoadAddress2.read().range(20, 16)]);
}

void registers_bank::memory_load()
{
    RegistersBank[WriteAddress.read()] = WriteData.read();
}

void registers_bank::memory_write()
{
    DataOut1.write(RegistersBank[LoadAddress1.read().range(25, 21)]);
}

void registers_bank::jump_cmp()
{
    DataOut1.write(RegistersBank[LoadAddress1.read().range(25, 21)]);
}

void registers_bank::print()
{
    std::cout << "=======Registradores=======" << std::endl;
    for (size_t i{0}; i < 32; i++)
    {
        std::cout << "[" << i << "]"
                  << "- (" << RegistersBank[i] << ")" << std::endl;
    }
    std::cout << std::endl;
}