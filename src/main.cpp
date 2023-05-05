#include "systemc.h"

#include "processor.cpp"

int sc_main(int argc, char *argv[])
{
    std:cout "Initializing processor..." << endl;

    processor prc{"Processor"};
    sc_clock clock("clock", 10, SC_NS, 0.5);
    prc.clock(clock);

    return 0;
}