# Makefile for 'SampleDrivers/ADIC' directory

ifndef TOP_DIR
TOP_DIR = ../../../
endif

include $(TOP_DIR)/common_variables.in

MORE_FLAGS = -I$(TOP_DIR)/build/include/ -L$(TOP_DIR)/build/lib/  -lColPack -DTOP_DIR=\"$(TOP_DIR)\"

% : %.cpp
	$(CC_COMPILER)  $(FLAGS) $(MORE_FLAGS) $< -o $@

DRIVERS = \
	01_Column_compression_and_recovery_for_Jacobian_return_Row_Compressed_Format \
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

