#include "systemc.h"

#include <vector>

SC_MODULE(data_memory)
{
    sc_in<sc_int<5>> AddressLoad, AddressWrite;
    sc_in<sc_int<32>> DataWriteIn;
    sc_in<bool> MemLoad, MemWrite;

    sc_out<sc_int<32>> DataLoadOut;

    sc_int<32> MemoryBank[32];

    void control();
    void memory_write();
    void memory_load();

    SC_CTOR(data_memory)
    {
        SC_METHOD(control);
        sensitive << AddressLoad << AddressWrite << DataWriteIn << DataLoadOut;
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
    MemoryBank[AddressWrite.read()] = DataWriteIn.read();
}

void data_memory::memory_load()
{
    DataLoadOut.write(MemoryBank[AddressLoad.read()]);
}