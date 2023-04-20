.PHONY: all

all: create

create:
	@echo "Compiling and executing the circuit..."
	g++ -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux64 -Wl -rpath=$SYSTEMC_HOME/lib-linux64 -o ../build/${EXECUTABLE} ${FILE} -lsystemc -lm
    ./build/${EXECUTABLE}