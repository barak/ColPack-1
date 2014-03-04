# Makefile for 'SampleDrivers' directory

ifndef TOP_DIR
TOP_DIR = ../
endif

include $(TOP_DIR)/common_variables.in

SUBDIRS = Basic ADOL-C_Matrix_Compression_and_Recovery

# TARGETS
all: all-drivers

.PHONY: all-drivers $(SUBDIRS)

$(SUBDIRS): banner
	@export TOP_DIR; $(MAKE) -C $@

all-drivers: $(SUBDIRS)

banner:
	@echo "###################################"
	@echo "### BUILDING ALL SAMPLE DRIVERS ###"
	@echo "###################################"
	@echo \


run-test:
	@for i in $(SUBDIRS) ; do \
	( export TOP_DIR=$(PWD); cd $$i && $(MAKE) run-test) ; \
	done

clean:
	@for i in $(SUBDIRS) ; do \
	( cd $$i && $(MAKE) clean) ; \
	done

wipe:
	@echo "Deleting files ..."
	@for i in $(SUBDIRS) ; do \
	( cd $$i && $(MAKE) wipe) ; \
	done

