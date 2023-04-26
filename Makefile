.PHONY: all

all: create

create:
	@echo "Compiling and executing the circuit..."
	g++ -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux64 -Wl -rpath=$SYSTEMC_HOME/lib-linux64 -o ../build/${EXECUTABLE} ${FILE} -lsystemc -lm
    ./build/${EXECUTABLE}

# SYSTEMC   = /usr/local/systemc
# INCDIR   += -I. -I$(SYSTEMC)/include
# LIBDIR   += -L$(SYSTEMC)/lib-linux  # That is a directory or a link to lib-linux dir
# LIBS     += -lsystemc
# CPPSRCS  +=  main.cpp req_reg.cpp routing_xy.cpp routing_wf.cpp routing_nl.cpp routing_nf.cpp routing_oe.cpp fifo_in.cpp  ifc_credit.cpp ifc_handshake.cpp irs.cpp fifo_out.cpp pg.cpp ppe.cpp ows.cpp ods.cpp ofc_credit.cpp ofc_handshake.cpp tg.cpp stopsim.cpp global_clock.cpp t_probe.cpp

# CPPOBJS   = $(CPPSRCS:.cpp=.o)
# OBJS      = $(CPPOBJS)
# CFLAGS    = -DXPIPES_SIMULATION
# CC        = g++

# system.x: $(OBJS)
# 	$(QUIET)$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBDIR) $(LIBS) 2>&1 | c++filt
# 	@echo $(ECHO)
# 	@echo "  [$(LINK)LINK$(DEFAULTCOLOR)]  :  $@"$(ECHO)
# 	@echo $(ECHO)

# %.o:    %.cpp
# 	$(QUIET)$(CC) $(CFLAGS) $(INCDIR) -c $<
# 	@echo "  [$(COMPILE)CC$(DEFAULTCOLOR)]    :  $@"$(ECHO)

# clean:
# 	rm -f *.x *~
# #	rm -f *.x *~ main.o req_reg.o fifo_in.o  ifc_credit.o ifc_handshake.o irs.o fifo_out.o pg.o ppe.o ows.o ods.o ofc_credit.o ofc_handshake.o x.o tg.o stopsim.o global_clock.o t_probe.o
# #  rm main.o req_reg.o routing_xy.o routing_wf.o routing_nl.o routing_nf.o fifo_in.o  ifc_credit.o ifc_handshake.o irs.o fifo_out.o pg.o ppe.o ows.o ods.o ofc_credit.o ofc_handshake.o tg.o stopsim.o global_clock.o t_probe.o


# ############## Color Codes
# RED          = _[01;31m
# GREEN        = _[01;32m
# YELLOW       = _[01;33m
# BLUE         = _[01;34m
# VIOLET       = _[01;35m
# CYAN         = _[01;36m
# WHITE        = _[01;37m
# DEFAULTCOLOR = _[00m
# PLAIN        =

# LINK         = $(RED)
# COMPILE      = $(BLUE)

# QUIET = @
# ECHO  =
