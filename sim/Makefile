# $Revision: 1.4 $$Date: 2003/09/22 14:06:09 $$Author: wsnyder $ -*- Makefile -*-
#*****************************************************************************
#
# DESCRIPTION: Verilator Example: Makefile for inside object directory
#
# This executed in the object directory, and called by ../Makefile
#
# Copyright 2004 by Wilson Snyder. This program is free software; you can
# redistribute it and/or modify it under the terms of either the GNU
# General Public License or the Perl Artistic License.
#
#*****************************************************************************

default:
	@echo "Please run 'make vl', 'make nc', 'make vcs', or 'make icarus'"
	false

PWD := $(shell pwd)

COMMON_FLAGS = -f ../input.vc
NC_FLAGS  = $(COMMON_FLAGS) \
	+ncsimargs+-status +nowarn+LIBNOU -q ../bench/bench.v
VCS_FLAGS = $(COMMON_FLAGS) \
	+twostate +define+vcs+1 ../bench/bench.v
VL_FLAGS  = $(COMMON_FLAGS) \
	--cc ../bench/k68_soc_test.v --exe $(PWD)/../bench/bench.cpp  -prefix m68 -Wno-WIDTH \
	-O3 -x-assign 0
ICARUS_FLAGS = $(COMMON_FLAGS) \
	-o simi \
	../bench/bench.v
VCOMP_FLAGS = $(COMMON_FLAGS) \
	-o simvc \
	$(wildcard ../bench/*.v) \
	../rtl/k68_adder.v \
	../rtl/k68_arb.v \
	../rtl/k68_asx.v \
	../rtl/k68_b2d.v \
	../rtl/k68_buni.v \
	../rtl/k68_calc.v \
	../rtl/k68_ccc.v \
	../rtl/k68_clkgen.v \
	../rtl/k68_cpu.v \
	../rtl/k68_d2b.v \
	../rtl/k68_decode.v \
	../rtl/k68_defines.v \
	../rtl/k68_dpmem.v \
	../rtl/k68_execute.v \
	../rtl/k68_fetch.v \
	../rtl/k68_load.v \
	../rtl/k68_lsx.v \
	../rtl/k68_par_mul.v \
	../rtl/k68_regbank.v \
	../rtl/k68_rox.v \
	../rtl/k68_roxx.v \
	../rtl/k68_sasc.v \
	../rtl/k68_soc.v \
	../rtl/sasc_brg.v \
	../rtl/sasc_fifo4.v \
	../rtl/sasc_top.v \

VBS_FLAGS = -o simi -y ../bench -y ../rtl \
	-I../bench -I../rtl \
	../bench/bench.v
CVER_FLAGS = $(COMMON_FLAGS) \
	../bench/bench.v

######################################################################

M32 = -m64
CPPFLAGS += $(M32)
LDFLAGS += $(M32)
# +~5% with -O3
OPT_FAST = $(M32) -O3

#OPT_FAST += -ggdb -fverbose-asm -S
#OPT_FAST += -pg
OPT_SLOW = $(OPT_FAST)
#LDFLAGS += -pg
export OPT_FAST
export OPT_SLOW
export LDFLAGS

vl:  vl_v vl_compile vl_sim
vl_v: 
	$(VERILATOR_ROOT)/bin/verilator $(VL_FLAGS)
vl_compile:
	( cd obj_dir ; make -f m68.mk )
vl_sim:
	time obj_dir/m68  10000000

m68.gprof:  vl
	gprof obj_dir/m68 > $@

vl_waves:
	$(VERILATOR_ROOT)/bin/verilator --trace $(VL_FLAGS)
	( cd obj_dir ; make -f m68.mk )
	time obj_dir/m68 -l sim.log

######################################################################

novcs:
	@echo "No VCS simulator installed."
	@echo "Not running VCS regression test."

vcs:
	vcs $(VCS_FLAGS)
	time ./simv -l sim.log

vcs_waves:
	vcs +cli -I $(VCS_FLAGS)
	time ./simv -l sim.log

######################################################################

nonc:
	@echo "No NC-Verilog simulator installed."
	@echo "Not running NC-Verilog regression test."

nc:
	time ncverilog $(NC_FLAGS)

nc_waves:
	time ncverilog +access+rc $(NC_FLAGS)

######################################################################

noicarus:
	@echo "No Icarus-Verilog simulator installed."
	@echo "Not running Icarus-Verilog regression test."

icarus:
	time iverilog $(ICARUS_FLAGS)
	time vvp simi

vcomp:
	time ~/src/verilator/vcomp-my/src/vcomp  $(VCOMP_FLAGS)
	./simvc

######################################################################

novbs:
	@echo "No Vbs simulator installed."
	@echo "Not running Vbs regression test."

vbs: 
	@echo "Need .vpp files made by vl"
	time vbs obj_dir/*.vpp

######################################################################

nocver:
	@echo "No Cver simulator installed."
	@echo "Not running Cver regression test."

cver: 
	time cver $(CVER_FLAGS)

######################################################################

maintainer-copy::
clean mostlyclean distclean maintainer-clean::
	-rm -rf obj_dir *.log *.dmp *.vpd simv* vcs.key csrc INCA_libs simi

