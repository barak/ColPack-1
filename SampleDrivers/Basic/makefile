# Makefile for 'SampleDrivers/Basic' directory

ifndef TOP_DIR
TOP_DIR = ../../
endif

include $(TOP_DIR)/common_variables.in

MORE_FLAGS = -I$(TOP_DIR)/build/include/ -L$(TOP_DIR)/build/lib/  -lColPack -DTOP_DIR=\"$(TOP_DIR)\"

% : %.cpp
	$(CC_COMPILER)  $(FLAGS) $(MORE_FLAGS) $< -o $@

DRIVERS = \
	color_bipartite_graph_using_BipartiteGraphBicoloringInterface \
	color_bipartite_graph_using_BipartiteGraphPartialColoringInterface \
	color_graph_using_GraphColoringInterface \
	Generate_seed_matrix_for_Hessian \
	Generate_seed_matrix_for_Jacobian \
	$(EXTRA_DRIVERS) \

.PHONY: run-test run-extra

# TARGETS
all: $(DRIVERS)


run-test:
	for i in $(DRIVERS) ; do \
	( export LD_LIBRARY_PATH=$(TOP_DIR)/build/lib; echo "run-test: Running ./$$i"; ./$$i) ; \
	done

run-extra: $(EXTRA_DRIVERS)
	for i in $(EXTRA_DRIVERS) ; do \
	( export LD_LIBRARY_PATH=$(TOP_DIR)/build/lib; echo "run-test: Running ./$$i"; ./$$i) ; \
	done

clean:
	@echo "Deleting files ..."
	rm -rf *~ *.o
wipe: clean
	@echo "Deleting files ..."
	rm -rf *.log
	@for i in $(DRIVERS) ; do \
	( rm -rf  $$i ) ; \
	done

