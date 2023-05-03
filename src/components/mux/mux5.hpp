#include "systemc.h"

SC_MODULE(mux5)
{
    sc_in<sc_int<5>> entry1, entry2;
    sc_in<sc_uint<1>> control;
    sc_out<sc_int<5>> out;

    // methods
    void select();

    SC_CTOR(mux5)
    {
        SC_METHOD(select);
        sensitive << control;
    }
};

void mux5::select()
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