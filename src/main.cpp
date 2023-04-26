#include "systemc.h"
#include "./components"

int sc_main(int argc, char* argv[]) {

    ula Ula("ULA");
    registers Registers("Registers");
    pc PC("PC");
    mux MuxUla("muxUla");
    instruction_memory InstMemory("InstMemory");
    data_memory DataMemory("DataMemory");

	return 0;
}