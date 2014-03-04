# Makefile for 'SampleDrivers/ADOL-C_Matrix_Compression_and_Recovery' directory

ifndef TOP_DIR
TOP_DIR = ../../
endif

include $(TOP_DIR)/common_variables.in

MORE_FLAGS = -I$(TOP_DIR)/build/include/ -L$(TOP_DIR)/build/lib/  -lColPack -DTOP_DIR=\"$(TOP_DIR)\"

% : %.cpp
	$(CC_COMPILER)  $(FLAGS) $(MORE_FLAGS) $< -o $@

DRIVERS = \
	01_Column_compression_and_recovery_for_Jacobian_return_Row_Compressed_Format \
	02_Column_compression_and_recovery_for_Jacobian_return_Coordinate_Format \
	03_Column_compression_and_recovery_for_Jacobian_return_Sparse_Solvers_Format \
	04_Row_compression_and_recovery_for_Jacobian_return_Row_Compressed_Format \
	05_Compression_and_direct_recovery_for_Hessian_return_Row_Compressed_Format \
	06_Compression_and_direct_recovery_for_Hessian_return_Coordinate_Format \
	07_Compression_and_direct_recovery_for_Hessian_return_Sparse_Solvers_Format \
	08_Compression_and_indirect_recovery_for_Hessian_return_Row_Compressed_Format \
	09_Bidirectional_compression_and_recovery_for_Jacobian_return_Row_Compressed_Format \
	10_Column_compression_and_recovery_for_Jacobian_return_Row_Compressed_Format__unmanaged_usermem \
	11_Compression_and_direct_recovery_for_Hessian_return_Row_Compressed_Format__unmanaged_usermem \
	12_Bidirectional_compression_and_recovery_for_Jacobian_return_Row_Compressed_Format__unmanaged_usermem \
	$(EXTRA_DRIVERS) \

.PHONY: run-test run-extra


# TARGETS
all: $(DRIVERS)


run-test:
	for i in $(DRIVERS) ; do \
	( export LD_LIBRARY_PATH=$(TOP_DIR)/build/lib; echo "run-test: Running ./$$i"; valgrind --tool=memcheck --leak-check=yes ./$$i) ; \
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

