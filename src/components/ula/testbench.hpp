#include "systemc.h"

SC_MODULE(testbench) {
	sc_out<sc_int<32>> A, B;
    sc_out<sc_uint<3>> Op;
	sc_in<bool> Clk;

	void TbGen() {
		wait();

        // AND
		A.write(1);
		B.write(0);
		Op.write(1);

		wait();

        // OR
		A.write(1);
		B.write(0);
		Op.write(2);

        wait();

        // XOR
		A.write(1);
		B.write(1);
		Op.write(3);

		wait();

        // NOT
		A.write(1);
		B.write(0);
		Op.write(4);

		wait();

        // CMP
		A.write(1);
		B.write(1);
		Op.write(5);

		wait();

        // ADD
		A.write(2);
		B.write(4);
		Op.write(6);

		wait();

        // SUB
        A.write(8);
		B.write(4);
		Op.write(7);

		wait();

		sc_stop();
	}

	SC_CTOR(testbench) {
		SC_THREAD(TbGen);
		sensitive << clk.pos().pos();
	}
};