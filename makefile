# Makefile for TOP directory
# #

include common_variables.in

# Common variables for modification
PACKAGE = ColPack
EXECUTABLE = $(PACKAGE).exe
LIBRARIES = lib$(PACKAGE)
INSTALL_DIR = .

# Redefine directories

SUBDIRS = Main Utilities GraphColoring BipartiteGraphBicoloring BipartiteGraphPartialColoring Recovery

# TARGETS

all: build-executable build-lib

.PHONY: build-executable build-lib build-SampleDrivers build-objs $(SUBDIRS)

build-objs: $(SUBDIRS)

$(SUBDIRS):
	@export TOP_DIR=$(PWD);$(MAKE) -C $@

Main: Utilities Recovery BipartiteGraphPartialColoring BipartiteGraphBicoloring GraphColoring

build-executable: build-objs
	@echo
	@echo "############################"
	@echo "### BUILDING EXECUTABLE ###"
	@echo "############################"
	@echo \

	$(CC_LINKER) $(FLAGS) -o $(EXECUTABLE) \
	GraphColoring/GraphCore.o \
	GraphColoring/GraphInputOutput.o \
	GraphColoring/GraphOrdering.o \
	GraphColoring/GraphColoring.o \
	GraphColoring/GraphColoringInterface.o \
	BipartiteGraphBicoloring/BipartiteGraphCore.o \
	BipartiteGraphBicoloring/BipartiteGraphInputOutput.o \
	BipartiteGraphBicoloring/BipartiteGraphOrdering.o \
	BipartiteGraphBicoloring/BipartiteGraphVertexCover.o \
	BipartiteGraphBicoloring/BipartiteGraphBicoloring.o \
	BipartiteGraphBicoloring/BipartiteGraphBicoloringInterface.o \
	BipartiteGraphPartialColoring/BipartiteGraphPartialOrdering.o \
	BipartiteGraphPartialColoring/BipartiteGraphPartialColoring.o \
	BipartiteGraphPartialColoring/BipartiteGraphPartialColoringInterface.o \
	Recovery/RecoveryCore.o \
	Recovery/HessianRecovery.o \
	Recovery/JacobianRecovery1D.o \
	Recovery/JacobianRecovery2D.o \
	Utilities/StringTokenizer.o \
	Utilities/DisjointSets.o \
	Utilities/File.o \
	Utilities/current_time.o \
	Utilities/Pause.o \
	Utilities/Timer.o \
	Utilities/command_line_parameter_processor.o \
	Utilities/MatrixDeallocation.o \
	Utilities/mmio.o \
	Utilities/stat.o \
	Utilities/extra.o \
	Main/Main.o \

	@echo " "
	@echo "Executable Created: $(INSTALL_DIR)/$(EXECUTABLE)"
	@echo " "
	-cp $(EXECUTABLE) $(INSTALL_DIR)

build-lib: build-objs

	@echo
	@echo "##########################"
	@echo "### BUILDING LIBRARIES ###"
	@echo "##########################"
	@echo \

	$(AR) $(LIBFLAGS) $(LIBRARIES).a \
	GraphColoring/GraphCore.o \
	GraphColoring/GraphInputOutput.o \
	GraphColoring/GraphOrdering.o \
	GraphColoring/GraphColoring.o \
	GraphColoring/GraphColoringInterface.o \
	BipartiteGraphBicoloring/BipartiteGraphCore.o \
	BipartiteGraphBicoloring/BipartiteGraphInputOutput.o \
	BipartiteGraphBicoloring/BipartiteGraphOrdering.o \
	BipartiteGraphBicoloring/BipartiteGraphVertexCover.o \
	BipartiteGraphBicoloring/BipartiteGraphBicoloring.o \
	BipartiteGraphBicoloring/BipartiteGraphBicoloringInterface.o \
	BipartiteGraphPartialColoring/BipartiteGraphPartialOrdering.o \
	BipartiteGraphPartialColoring/BipartiteGraphPartialColoring.o \
	BipartiteGraphPartialColoring/BipartiteGraphPartialColoringInterface.o \
	Recovery/RecoveryCore.o \
	Recovery/HessianRecovery.o \
	Recovery/JacobianRecovery1D.o \
	Recovery/JacobianRecovery2D.o \
	Utilities/StringTokenizer.o \
	Utilities/DisjointSets.o \
	Utilities/File.o \
	Utilities/current_time.o \
	Utilities/Pause.o \
	Utilities/Timer.o \
	Utilities/MatrixDeallocation.o \
	Utilities/mmio.o \
	Utilities/stat.o \
	Utilities/extra.o \

	$(RANLIB) $(LIBRARIES).a

	-${CXX}	${CXXFLAGS} -shared -Wl,-soname,$(LIBRARIES).so -o $(LIBRARIES).so \
	GraphColoring/GraphCore.o \
	GraphColoring/GraphInputOutput.o \
	GraphColoring/GraphOrdering.o \
	GraphColoring/GraphColoring.o \
	GraphColoring/GraphColoringInterface.o \
	BipartiteGraphBicoloring/BipartiteGraphCore.o \
	BipartiteGraphBicoloring/BipartiteGraphInputOutput.o \
	BipartiteGraphBicoloring/BipartiteGraphOrdering.o \
	BipartiteGraphBicoloring/BipartiteGraphVertexCover.o \
	BipartiteGraphBicoloring/BipartiteGraphBicoloring.o \
	BipartiteGraphBicoloring/BipartiteGraphBicoloringInterface.o \
	BipartiteGraphPartialColoring/BipartiteGraphPartialOrdering.o \
	BipartiteGraphPartialColoring/BipartiteGraphPartialColoring.o \
	BipartiteGraphPartialColoring/BipartiteGraphPartialColoringInterface.o \
	Recovery/RecoveryCore.o \
	Recovery/HessianRecovery.o \
	Recovery/JacobianRecovery1D.o \
	Recovery/JacobianRecovery2D.o \
	Utilities/StringTokenizer.o \
	Utilities/DisjointSets.o \
	Utilities/File.o \
	Utilities/current_time.o \
	Utilities/Pause.o \
	Utilities/Timer.o \
	Utilities/MatrixDeallocation.o \
	Utilities/mmio.o \
	Utilities/stat.o \
	Utilities/extra.o \

	@for i in $(SUBDIRS) ; do \
	( cd $$i && $(MAKE) install); \
	done

	# create build directory
	mkdir -p build/include
	mkdir -p build/lib

	# copy header files to ./build/include
	@for i in $(SUBDIRS) ; do \
	( cp $$i/*.h build/include); \
	done

	# copy libraries to ./build/lib
	cp $(LIBRARIES).a build/lib
	-cp $(LIBRARIES).so build/lib

all-clean: all clean

clean: clean-banner clean-SampleDrivers

	-rm -rf *~ *.o 	Graphs/*~ 
	-rm -f SampleDrivers/ADOL-C_Matrix_Compression_and_Recovery/*~  SampleDrivers/Basic/*~
	@for i in $(SUBDIRS) ; do \
	( export TOP_DIR=$(PWD);cd $$i && $(MAKE) clean) ; \
	done

clean-banner:
	@echo
	@echo "################"
	@echo "### CLEAN UP ###"
	@echo "################"
	@echo \

clean-SampleDrivers:
	@ export TOP_DIR=$(PWD);$(MAKE) -C SampleDrivers clean

ship: wipe
	-rm -rf *.vcproj* *.ncb *.sln *.suo debug Debug core ColPack.exe libColPack.a libColPack.so build
	d2ua
	(cd .. && dz ColPack;chmod 755 ColPack.tar.gz;)

ship-dev: ship
	doxygen ../../../doxygen/ColPack_local_ubuntu_ship_html2
	chmod -R 755 ~/public_html/dox/

install:
	@echo
	@echo "################################"
	@echo "### INSTALL EXECUTABLE FILES ###"
	@echo "################################"
	@echo \






wipe: wipe-banner wipe-SampleDrivers

	-rm -rf *~ *.o *.log core $(EXECUTABLE) $(LIBRARIES)*  	Graphs/*~ 
	@for i in $(SUBDIRS) ; do \
	( export TOP_DIR=$(PWD);cd $$i && $(MAKE) wipe) ; \
	done

wipe-banner:
	@echo
	@echo "#################################################"
	@echo "### WIPE EVERYTHING INCLUDING THE EXECUTABLES ###"
	@echo "#################################################"
	@echo \

wipe-SampleDrivers:
	@export TOP_DIR=$(PWD);$(MAKE) -C SampleDrivers wipe

# Rules to build individual targets
build-SampleDrivers: build-lib
	@export TOP_DIR=$(PWD); $(MAKE) -C SampleDrivers

test: build-SampleDrivers test-banner

test-banner:
	@echo
	@echo "####################################################################################"
	@echo " Note: If you got (symbol lookup error ... undefined symbol) when running the driver"
	@echo "###     Please make sure that your LD_LIBRARY_PATH contains libColPack.so  #########"
	@echo "####################################################################################"
	@echo \



run-test: test
	@export TOP_DIR=$(PWD); $(MAKE) -C SampleDrivers run-test
