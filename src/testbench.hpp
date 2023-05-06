#include "systemc.h"

SC_MODULE(testbench)
{
    sc_in_clk clock;

    void test()
    {
        for (size_t i{0}; i < 10; i++)
        {
            wait();
        }

        sc_stop();
    }

    SC_CTOR(testbench)
    {
        SC_THREAD(test);
        sensitive << clock.pos();
    }
};