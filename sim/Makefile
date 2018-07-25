#*****************************************************************************
#
# DESCRIPTION: verilog-sim-benchmarks Makefile
#
# Copyright 2006-2009 by Wilson Snyder. This program is free software; you can
# redistribute it and/or modify it under the terms of either the GNU
# General Public License or the Perl Artistic License.
#
#*****************************************************************************

default: help

CC := /usr/bin/gcc
RM := /bin/rm
PWD := $(shell pwd)
BENCHMARKER := perl benchmarker

COMMON_FLAGS = -f ../input.vc

GCC_PLIFLAGS = -fPIC -shared -o benchmark_pli.so \
			   ../bench/veriuser.c \
			   ../bench/benchmark_pli.c

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

######################################################################
machine:
	@uname -a
	@cat /etc/*release
	@gcc --version | head
	@grep -i 'model name' /proc/cpuinfo
	@lshw

######################################################################

VERILATOR_EXE = verilator
VERILATOR_VERSION = $(shell $(VERILATOR_EXE) --version)
VERILATOR_FLAGS  = $(COMMON_FLAGS) \
	--cc ../bench/k68_soc_test.v --exe $(PWD)/../bench/bench.cpp  -prefix m68 -Wno-WIDTH \
	-O3 -x-assign 0

ALL_SIMS += vlt-32
vlt-32:
	$(VERILATOR_EXE) $(VERILATOR_FLAGS)
	( cd obj_dir ; $(RM) *.o ; make -j -f m68.mk LDFLAGS=-m32 OPT_FAST="-m32 -O3" OPT_SLOW="-m32 -O3" )
	$(BENCHMARKER) "$@ $(VERILATOR_VERSION)" "obj_dir/m68 %c"

ALL_SIMS += vlt-64
vlt-64:
	$(VERILATOR_EXE) $(VERILATOR_FLAGS)
	( cd obj_dir ; $(RM) *.o ; make -j -f m68.mk LDFLAGS=-m64 OPT_FAST="-m64 -O3" OPT_SLOW="-m64 -O3" )
	$(BENCHMARKER) "$@ $(VERILATOR_VERSION)" "obj_dir/m68 %c"

ALL_SIMS += vlt-32-mt
vlt-32-mt:
	$(VERILATOR_EXE) --threads `nproc` $(VERILATOR_FLAGS)
	( cd obj_dir ; $(RM) *.o ; make -j -f m68.mk LDFLAGS=-m32 OPT_FAST="-m32 -O3" OPT_SLOW="-m32 -O3" )
	$(BENCHMARKER) "$@ $(VERILATOR_VERSION)" "obj_dir/m68 %c"

ALL_SIMS += vlt-64-mt
vlt-64-mt:
	$(VERILATOR_EXE) --threads `nproc` $(VERILATOR_FLAGS)
	( cd obj_dir ; $(RM) *.o ; make -j -f m68.mk LDFLAGS=-m64 OPT_FAST="-m64 -O3" OPT_SLOW="-m64 -O3" )
	$(BENCHMARKER) "$@ $(VERILATOR_VERSION)" "obj_dir/m68 %c"

m68.gprof:  vlt
	gprof obj_dir/m68 > $@

vlt-waves:
	$(VERILATOR_EXE) --trace $(VLT_FLAGS)
	( cd obj_dir ; make -f m68.mk )
	time obj_dir/m68 -l sim.log

######################################################################

VCS_EXE ?= $(value VERILATOR_VCS)
VCS_EXE ?= $(value VCS)
VCS_EXE = vcs
VCS_VERSION = $(shell $(VCS_EXE) -ID 2>&1 | grep 'version =')
VCS_FLAGS = $(COMMON_FLAGS) \
	+define+vcs+1 ../bench/bench.v
VCS_GCC = $(CC)
VCS_GCC_PLIFLAGS = -DVCS -P ../bench/vcs_pli.tab \
				   ../bench/benchmark_pli.c
				   
ALL_SIMS += vcs-32-2state
vcs-32-2state:
	-$(RM) -rf csrc simv.daidir
	$(VCS_EXE) $(VCS_FLAGS)
	$(BENCHMARKER) "$@ $(VCS_VERSION)" "./simv +CYCLES=%c +2state"

ALL_SIMS += vcs-64-2state
vcs-64-2state:
	-$(RM) -rf csrc simv.daidir
	$(VCS_EXE) $(VCS_FLAGS) -full64
	$(BENCHMARKER) "$@ $(VCS_VERSION)" "./simv +CYCLES=%c +2state"

ALL_SIMS += vcs-32-4state
vcs-32-4state:
	-$(RM) -rf csrc simv.daidir
	$(VCS_EXE) $(VCS_FLAGS)
	$(BENCHMARKER) "$@ $(VCS_VERSION)" "./simv +CYCLES=%c"

ALL_SIMS += vcs-64-4state
vcs-64-4state:
	-$(RM) -rf csrc simv.daidir
	$(VCS_EXE) $(VCS_FLAGS) -full64
	$(BENCHMARKER) "$@ $(VCS_VERSION)" "./simv +CYCLES=%c"

vcs-64-4state_pli:
	-$(RM) -rf csrc simv.daidir
	$(VCS_EXE) $(VCS_FLAGS) -full64 +define+BENCHMARK_PLI -cc $(VCS_GCC) $(VCS_GCC_PLIFLAGS) 
	$(BENCHMARKER) "$@ $(VCS_VERSION)" "./simv +CYCLES=%c"

vcs-waves:
	$(VCS_EXE) +cli -I $(VCS_FLAGS)
	time ./simv -l sim.log

######################################################################

NC_EXE ?= $(value VERILATOR_NCVERILOG)
NC_EXE ?= $(value NCVERILOG)
NC_EXE = ncverilog
NC_VERSION = $(shell $(NC_EXE) -version)
NC_GCC = $(CC)
NC_GCC_PLIFLAGS = $(GCC_PLIFLAGS) \
				  -DNC -I../bench/include/nc

NC_FLAGS  = $(COMMON_FLAGS) \
	+ncsimargs+-status +nowarn+LIBNOU -q ../bench/bench.v
NC_RUN_FLAGS = -R

ALL_SIMS += nc-32
nc-32:
	$(NC_EXE) $(NC_FLAGS) -c
	$(BENCHMARKER) "$@ $(NC_VERSION)" "$(NC_EXE) $(NC_RUN_FLAGS) +CYCLES=%c"

ALL_SIMS += nc-64
nc-64:
	$(NC_EXE) $(NC_FLAGS) +nc64bit -c
	$(BENCHMARKER) "$@ $(NC_VERSION)" "$(NC_EXE) $(NC_RUN_FLAGS) +CYCLES=%c +nc64bit"

nc-64_pli:
	$(NC_GCC) $(NC_GCC_PLIFLAGS) 
	$(NC_EXE) $(NC_FLAGS) +nc64bit -c +define+BENCHMARK_PLI +acc +loadpli1=./benchmark_pli.so:bootstrap
	$(BENCHMARKER) "$@ $(NC_VERSION)" "$(NC_EXE) $(NC_RUN_FLAGS) +CYCLES=%c +nc64bit"

nc-waves:
	time ncverilog +access+rc $(NC_FLAGS)

######################################################################

ICARUS_EXE ?= $(value VERILATOR_IVERILOG)
ICARUS_EXE ?= $(value IVERILOG)
ICARUS_EXE = iverilog
ICARUS_VERSION = $(shell $(ICARUS_EXE) -V 2>&1 | head -1)
ICARUS_FLAGS = $(COMMON_FLAGS) \
	-o simi \
	../bench/bench.v
ICARUS_GCC = $(CC)
ICARUS_GCC_PLIFLAGS = $(GCC_PLIFLAGS) \
					  -DNC -I../bench/include/nc

ICARUS_PLI_FLAGS = -cadpli=benchmark_pli.so:bootstrap

ALL_SIMS += icarus
icarus:
	time $(ICARUS_EXE) $(ICARUS_FLAGS)
	$(BENCHMARKER) "icarus $(ICARUS_VERSION)" "./simi +CYCLES=%c"

icarus_pli:
	time $(ICARUS_GCC) $(ICARUS_GCC_PLIFLAGS) 
	time $(ICARUS_EXE) $(ICARUS_FLAGS) -DBENCHMARK_PLI
	$(BENCHMARKER) "icarus $(ICARUS_VERSION)" "vvp -mcadpli ./simi $(ICARUS_PLI_FLAGS) +CYCLES=%c"

######################################################################

ALL_SIMS += vcomp
vcomp:
	time ~/src/verilator/vcomp-my/src/vcomp  $(VCOMP_FLAGS)
	./simvc

######################################################################

ALL_SIMS += vbs
vbs: 
	@echo "Need .vpp files made by vlt"
	time vbs obj_dir/*.vpp

######################################################################

CVER_EXE ?= $(value VERILATOR_CVER)
CVER_EXE ?= $(value CVER)
CVER_EXE ?= cver
CVER_VERSION = $(shell $(CVER_EXE) -V 2>&1 | head -1)
CVER_FLAGS = $(COMMON_FLAGS) \
	+verbose \
	../bench/bench.v

ALL_SIMS += cver
cver: 
	$(BENCHMARKER) "$(CVER_EXE) $(CVER_VERSION)" "$(CVER_EXE) $(CVER_FLAGS) +CYCLES=%c"

######################################################################

CVC_EXE ?= $(value VERILATOR_CVC)
CVC_EXE ?= $(value CVC)
CVC_EXE = cvc
CVC64_EXE ?= $(value VERILATOR_CVC64)
CVC64_EXE ?= $(value CVC64)
CVC64_EXE = cvc64
CVC_VERSION = $(shell $(CVC_EXE) -V 2>&1 | head -1)
CVC64_VERSION = $(shell $(CVC64_EXE) -V 2>&1 | head -1)
#cvc regular optimize -O
CVC_FLAGS = $(COMMON_FLAGS) -O +verbose ../bench/bench.v
CVC_GCC = $(CC)
CVC_GCC_PLIFLAGS = $(GCC_PLIFLAGS) \
				   -DCVC -I../bench/include/cvc

#cvc regular -O +nbaopt
CVC_NBAOPT_FLAGS = $(COMMON_FLAGS) -O +nbaopt +verbose ../bench/bench.v
CVC_2STATE_FLAGS = $(COMMON_FLAGS) -O +2state +verbose ../bench/bench.v
#cvc interpreter
CVC_INTERP_FLAGS = $(COMMON_FLAGS) +verbose +interp ../bench/bench.v

ALL_SIMS += cvc
cvc: 
	time $(CVC_EXE) $(CVC_FLAGS)
	$(BENCHMARKER) "$(CVC_EXE) $(CVC_VERSION)" "./cvcsim +CYCLES=%c"

cvc_nbaopt: 
	time $(CVC_EXE) $(CVC_NBAOPT_FLAGS)
	$(BENCHMARKER) "$(CVC_EXE) $(CVC_VERSION)" "./cvcsim +CYCLES=%c"

ALL_SIMS += cvc64
cvc64: 
	time $(CVC64_EXE) $(CVC_FLAGS)
	$(BENCHMARKER) "$(CVC64_EXE) $(CVC64_VERSION)" "./cvcsim +CYCLES=%c"

cvc64_pli: 
	time $(CVC_GCC) $(CVC_GCC_PLIFLAGS) 
	time $(CVC64_EXE) $(CVC_FLAGS) +define+BENCHMARK_PLI +acc +loadpli1=./benchmark_pli.so:bootstrap
	$(BENCHMARKER) "$(CVC64_EXE) $(CVC64_VERSION)" "./cvcsim +CYCLES=%c"

cvc_nbaopt64: 
	time $(CVC64_EXE) $(CVC_NBAOPT_FLAGS)
	$(BENCHMARKER) "$(CVC64_EXE) $(CVC64_VERSION)" "./cvcsim +CYCLES=%c"

cvc_2state64: 
	time $(CVC64_EXE) $(CVC_2STATE_FLAGS)
	$(BENCHMARKER) "$(CVC64_EXE) $(CVC64_VERSION)" "./cvcsim +CYCLES=%c"

cvc_interp: 
	$(BENCHMARKER) "$(CVC_EXE) $(CVC_VERSION)" "$(CVC_EXE) $(CVC_INTERP_FLAGS) +CYCLES=%c"

cvc_interp64: 
	$(BENCHMARKER) "$(CVC64_EXE) $(CVC_VERSION)" "$(CVC64_EXE) $(CVC_INTERP_FLAGS) +CYCLES=%c"

######################################################################

help:
	@echo "Please make one of the below targets (not in parallel):"
	@echo "   machine     Show machine information"
	@echo "   clean       Remove temp files"
	@echo $(ALL_SIMS)
	false

maintainer-copy::
clean mostlyclean distclean maintainer-clean::
	-$(RM) -rf obj_dir *.log *.dmp *.vpd simv* vcs.key csrc INCA_libs simi .vcsmx_rebuild ucli.key


