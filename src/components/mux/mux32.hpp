#include "systemc.h"

SC_MODULE(mux32)
{
    sc_in<sc_int<32>> entry1, entry2;
    sc_in<sc_uint<1>> control;
    sc_out<sc_int<32>> out;

    // methods
    void select();

    SC_CTOR(mux32)
    {
        SC_METHOD(select);
        sensitive << control;
    }
};

void mux32::select()
{
    if (control.read())
    {
        out.write(entry1.read());
    }
    else
    {
        out.write(entry2.read());
    }
}