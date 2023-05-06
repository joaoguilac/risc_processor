#include "systemc.h"
// #include "sysc/utils/sc_vector.h"

#include <vector>

SC_MODULE(registers_bank)
{
    sc_in<sc_uint<5>> LoadAddress1, LoadAddress2, WriteAddress;
    sc_in<sc_int<32>> WriteData;
    sc_in<bool> RegWrite, MemWrite, RegUla;
    sc_in_clk clock;

    sc_out<sc_int<32>> DataOut1, DataOut2;

    sc_int<32> RegistersBank[32];

    // methods
    void control();
    void ula_load();
    void memory_load();
    void memory_write();

    SC_CTOR(registers_bank)
    {
        SC_METHOD(control);
        sensitive << clock.pos();
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
}

void registers_bank::ula_load()
{
    DataOut1.write(RegistersBank[LoadAddress1.read()]);
    DataOut2.write(RegistersBank[LoadAddress2.read()]);
}

void registers_bank::memory_load()
{
    RegistersBank[WriteAddress.read()] = WriteData.read();
}

void registers_bank::memory_write()
{
    DataOut1.write(RegistersBank[LoadAddress1.read()]);
}
