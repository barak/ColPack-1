# Makefile for 'Recovery' directory

ifndef TOP_DIR
TOP_DIR = ../
endif

include $(TOP_DIR)/common_variables.in

#Header files
HEADERFILES  =  $(COMMON_HEADER_FILES) \


# TARGETS
all: HessianRecovery.o \
	JacobianRecovery1D.o \
	JacobianRecovery2D.o \
	RecoveryCore.o \


RecoveryCore.o: $(HEADERFILES) RecoveryCore.h RecoveryCore.cpp

HessianRecovery.o: $(HEADERFILES) HessianRecovery.h HessianRecovery.cpp

JacobianRecovery1D.o: $(HEADERFILES) JacobianRecovery1D.h JacobianRecovery1D.cpp

JacobianRecovery2D.o: $(HEADERFILES) JacobianRecovery2D.h JacobianRecovery2D.cpp

install:

clean:
	@echo "Deleting files ..."
	rm -rf *~ *.o
wipe:
	@echo "Deleting files ..."
	rm -rf *~ *.o *.log
