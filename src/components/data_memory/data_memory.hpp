#include "systemc.h"

#include <vector>

SC_MODULE(data_memory)
{
    sc_in<sc_uint<5>> AddressLoad, AddressWrite;
    sc_in<sc_uint<32>> DataWriteIn;
    sc_in<bool> MemLoad, MemWrite;
    sc_in_clk clock;

    sc_out<sc_uint<32>> DataLoadOut;

    sc_uint<32> MemoryBank[32];

    // methods
    void control();
    void memory_write();
    void memory_load();
    void print();

    SC_CTOR(data_memory)
    {
        SC_METHOD(control);
        sensitive << AddressLoad << AddressWrite << DataWriteIn << DataLoadOut << MemLoad << MemWrite;
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

void data_memory::print()
{
    std::cout << "=======Memória de Dados=======" << std::endl;
    for (size_t i{0}; i < 32; i++)
    {
        std::cout << "[" << i << "]"
                  << "- (" << MemoryBank[i] << ")" << std::endl;
    }
    std::cout << std::endl;
}