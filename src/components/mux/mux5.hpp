#include "systemc.h"

SC_MODULE(mux5)
{
    sc_in<sc_uint<5>> Entry1, Entry2;
    sc_in<bool> Control;
    sc_in_clk clock;

    sc_out<sc_uint<5>> Out;

    // methods
    void select();

    SC_CTOR(mux5)
    {
        SC_METHOD(select);
        sensitive << Control << Entry1 << Entry2;
    }
};

void mux5::select()
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