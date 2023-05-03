#include "systemc.h"

SC_MODULE(data_memory)
{
    sc_in<sc_uint<5>> address_load, address_write;
    sc_in<sc_int<32>> data_write_in;
    sc_in<sc_uint<1>> memWrite, memLoad;
    sc_out<sc_int<32>> data_load_out;

    sc_vector<sc_int<32>> memory_bank[32];

    sc_clock clk("clk", 10, SC_NS, 0.5);

    void control();

    SC_CTOR(data_memory)
    {
        SC_METHOD(control);
        sensitive << clk;
    }
};

void data_memory::control()
{
    if (memWrite.read())
        memory_write();
    else if (memLoad.read())
        memory_load();
}

void memory_write()
{
    memory_bank[address_write.read()].write(data_write_in.read());
}

void memory_load()
{
    data_load_out.write(memory_bank[address_load.read()]);
}