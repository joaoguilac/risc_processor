#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(registers)
{
    sc_in<sc_uint<5>> load_address1, load_address2, write_address;
    sc_in<sc_int<32>> write_data;
    sc_in<sc_uint<1>> RegWrite, MemWrite, RegUla;
    sc_clock clk("clk", 10, SC_NS, 0.5);
    sc_out<sc_int<32>> data_out1, data_out2;

    sc_vector<sc_int<32>> registers_bank[32];

    // methods
    void control();

    SC_CTOR(registers)
    {
        SC_METHOD(control);
        sensitive << clk;
    }
};

void registers::control()
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
    data_out1.write(registers_bank[load_address1.read()]);
    data_out2.write(registers_bank[load_address2.read()]);
}

void memory_load()
{
    registers_bank[write_address.read()].write(write_data.read());
}

void memory_write()
{
    data_out1.write(registers_bank[load_address1.read()]);
}
