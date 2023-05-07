#include "systemc.h"

#include <vector>

SC_MODULE(data_memory)
{
    sc_in<sc_int<5>> AddresLoad, AddresWrite;
    sc_in<sc_int<32>> DataWriteIn;
    sc_in<bool> MemWrite, MemLoad;
    sc_in_clk clock;

    sc_out<sc_int<32>> DataLoadOut;

    sc_int<32> MemoryBank[32];

    void control();
    void memory_write();
    void memory_load();

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

void data_memory::memory_write()
{
    MemoryBank[AddresWrite.read()] = DataWriteIn.read();
}

void data_memory::memory_load()
{
    DataLoadOut.write(MemoryBank[AddresLoad.read()]);
}