#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(registers_bank)
{
    sc_in<sc_uint<5>> LoadAddress1, LoadAddress2, WriteAddress;
    sc_in<sc_int<32>> WriteData;
    sc_in<bool> RegWrite, MemWrite, RegUla;
    sc_out<sc_int<32>> DataOut1, DataOut2;

    sc_vector<sc_int<32>> RegistersBank[32];

    sc_port<sc_signal_in_if<bool>> clock;

    // methods
    void control();

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

void ula_load()
{
    DataOut1.write(RegistersBank[LoadAddress1.read()]);
    DataOut2.write(RegistersBank[LoadAddress2.read()]);
}

void memory_load()
{
    RegistersBank[WriteAddress.read()].write(WriteData.read());
}

void memory_write()
{
    DataOut1.write(RegistersBank[LoadAddress1.read()]);
}
