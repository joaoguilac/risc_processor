#include "systemc.h"

SC_MODULE(data_memory)
{
    sc_in<sc_uint<5>> AddresLoad, AddresWrite;
    sc_in<sc_int<32>> DataWriteIn;
    sc_in<bool> MemWrite, MemLoad;
    sc_in_clk clock;

    sc_out<sc_int<32>> DataLoadOut;

    sc_vector<sc_int<32>> MemoryBank[32];

    void control();

    SC_CTOR(data_memory)
    {
        SC_METHOD(control);
        sensitive << clock.pos();
    }
};

void data_memory::control()
{
    if (MemWrite.read())
        memory_write();
    else if (MemLoad.read())
        memory_load();
}

void memory_write()
{
    MemoryBank[AddresWrite.read()].write(DataWriteIn.read());
}

void memory_load()
{
    DataLoadOut.write(MemoryBank[AddresLoad.read()]);
}