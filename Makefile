CC       := g++ # This is the main compiler
BUILDDIR := build
INC 	 := -I include
CFLAGS   := $(shell root-config --cflags) -g -O3 #-Wno-write-strings -D_FILE_OFFSET_BITS=64 -DDROP_CGAL #-Wall -Wextra
ROOTLIBS := $(shell root-config --libs) -lMinuit -lMLP -lXMLIO -lTMVA -lGenVector

#TARGET   := bin/tprimetHHadronicLooper bin/covMatrix_Looper bin/tprimetHHadronicMVABabyMaker
#TARGET   := bin/tprimetHHadronicLooper bin/tprimetHHadronicLooper_v2p7 bin/tprimetHHadronicMVABabyMaker bin/tprimetHHadronicMVABabyMaker_v2p7
TARGET   := bin/tprimetHHadronicLooper bin/tprimetHHadronicMVABabyMaker

all: ${TARGET}

build/jsoncpp.o: src/jsoncpp.cpp include/json/json.h
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/sorting.o: src/sorting.cc include/sorting.h
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/truth_matching.o: src/truth_matching.cc include/truth_matching.h include/sorting.h
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/chi2_helper.o: src/chi2_helper.cc include/chi2_helper.h include/json/json.h
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

#build/tprimetHHadronicLooper.o: src/tprimetHHadronicLooper.cpp src/ScanChain_tprimetHHadronic.C src/ScanChain_tprimetHHadronic_signal.C src/ScanChain_tprimetHHadronic_ttH.C include/ScanChain.h include/ScanChain_ttH.h include/ttHLooper.h include/ttHLooper_ttH.h include/chi2_helper.h include/truth_matching.h include/sorting.h
#	@mkdir -p $(BUILDDIR)
#	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

#build/tprimetHHadronicLooper.o: src/tprimetHHadronicLooper.cpp src/ScanChain_tprimetHHadronic.C include/ScanChain.h include/ttHLooper.h include/chi2_helper.h include/truth_matching.h include/sorting.h
#	@mkdir -p $(BUILDDIR)
#	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/tprimetHHadronicLooper.o: src/tprimetHHadronicLooper.cpp src/ScanChain_tprimetHHadronic_signal.C include/ScanChain.h include/ttHLooper.h include/chi2_helper.h include/truth_matching.h include/sorting.h
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/tprimetHHadronicLooper_v2p7.o: src/tprimetHHadronicLooper_v2p7.cpp src/ScanChain_tprimetHHadronic_signal_v2p7.C include/ScanChain_v2p7.h include/ttHLooper.h include/chi2_helper.h include/truth_matching.h include/sorting.h
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

#build/tprimetHHadronicLooper.o: src/tprimetHHadronicLooper.cpp src/ScanChain_tprimetHHadronic_ttH.C include/ScanChain_ttH.h include/ttHLooper_ttH.h include/chi2_helper.h include/truth_matching.h include/sorting.h
#	@mkdir -p $(BUILDDIR)
#	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/tprimetHHadronicMVABabyMaker.o: src/tprimetHHadronicMVABabyMaker.cpp src/MakeMVABabies_tprimetHHadronic.C include/MakeMVABabies_ttHHadronic.h include/ScanChain.h include/chi2_helper.h include/sorting.h include/ttHLooper.h
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/tprimetHHadronicMVABabyMaker_v2p7.o: src/tprimetHHadronicMVABabyMaker_v2p7.cpp src/MakeMVABabies_tprimetHHadronic_v2p7.C include/MakeMVABabies_ttHHadronic.h include/ScanChain_v2p7.h include/chi2_helper.h include/sorting.h include/ttHLooper.h
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

bin/tprimetHHadronicLooper: build/tprimetHHadronicLooper.o build/chi2_helper.o build/truth_matching.o build/sorting.o build/jsoncpp.o
	@echo "Linking..." && mkdir -p bin
	$(CC) -o $@ $^ $(CFLAGS) $(ROOTLIBS)

bin/tprimetHHadronicLooper_v2p7: build/tprimetHHadronicLooper_v2p7.o build/chi2_helper.o build/truth_matching.o build/sorting.o build/jsoncpp.o
	@echo "Linking..." && mkdir -p bin
	$(CC) -o $@ $^ $(CFLAGS) $(ROOTLIBS)

bin/tprimetHHadronicMVABabyMaker: build/tprimetHHadronicMVABabyMaker.o build/chi2_helper.o build/sorting.o build/jsoncpp.o
	@echo "Linking..." && mkdir -p bin
	$(CC) -o $@ $^ $(CFLAGS) $(ROOTLIBS)

bin/tprimetHHadronicMVABabyMaker_v2p7: build/tprimetHHadronicMVABabyMaker_v2p7.o build/chi2_helper.o build/sorting.o build/jsoncpp.o
	@echo "Linking..." && mkdir -p bin
	$(CC) -o $@ $^ $(CFLAGS) $(ROOTLIBS)

# cov. matrix study
build/covMatrix_Looper.o: src/covMatrix_Looper.cpp src/covMatrix_ScanChain.C include/ScanChain.h include/truth_matching.h include/sorting.h
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

bin/covMatrix_Looper: build/covMatrix_Looper.o build/truth_matching.o build/sorting.o
	@echo "Linking..." && mkdir -p bin
	$(CC) -o $@ $^ $(CFLAGS) $(ROOTLIBS)

.PHONY: clean

clean:
	@echo " Cleaning..."; 
	$(RM) -r $(BUILDDIR) $(TARGET)
