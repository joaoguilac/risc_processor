#include "systemc.h"

SC_MODULE(mux32)
{
    sc_in<sc_int<32>> Entry1, Entry2;
    sc_in<bool> Control;

    sc_out<sc_int<32>> Out;

    // methods
    void select();

    SC_CTOR(mux32)
    {
        SC_METHOD(select);
        sensitive << Control << Entry1 << Entry2;
    }
};

void mux32::select()
{
    if (Control.read())
    {
        Out.write(Entry1.read());
    }
    else
    {
        Out.write(Entry2.read());
    }
}