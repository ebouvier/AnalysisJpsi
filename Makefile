CXXFLAGS = -g -Wall -std=c++0x -fPIC -Wno-deprecated -I. -I`root-config --incdir` #-std=c++0x dire à g++ d'utiliser le c++11 au moment de la compilation
LDFLAGS = -g -I.
CXX = c++
DEPS =  $(patsubst %.cc, %.d, $(wildcard *.cc)) 

all: run

run: MyAna.o runMyAna.o  MetRes.o TopTriggerEfficiencyProvider.o rochcor2012v2.o PUReweighter.o
	${CXX} ${LDFLAGS} -o runMyAna $^ `root-config --libs`

runMyAna.o: runMyAna.cc
	${CXX} -c ${CXXFLAGS} `root-config --cflags` runMyAna.cc

MyAna.o: MyAna.cc 
	${CXX} -c ${CXXFLAGS} `root-config --cflags` MyAna.cc

MetRes.o: MetRes.cc 
	${CXX} -c ${CXXFLAGS} `root-config --cflags` MetRes.cc

TopTriggerEfficiencyProvider.o: TopTriggerEfficiencyProvider.cc 
	${CXX} -c ${CXXFLAGS} `root-config --cflags` TopTriggerEfficiencyProvider.cc

rochcor2012v2.o: rochcor2012v2.cc
	${CXX} -c ${CXXFLAGS} `root-config --cflags` rochcor2012v2.cc

PUReweighter.o: PUReweighter.cpp 
	${CXX} -c ${CXXFLAGS} `root-config --cflags` PUReweighter.cpp
clean:
	rm -f MyAna.o runMyAna.o MetRes.o TopTriggerEfficiencyProvider.o rochcor2012v2.o PUReweighter.o runMyAna core *.d


# Make the dependencies 
# If one of the .h included in the different .cc is modified, it will be automatically recompiled
%.d: %.cc
	@echo "Generating dependencies for $<"
	@set -e; $(CXX) -M $(CXXFLAGS) $< \
	| sed 's%\($*\)\.o[ :]*%\1.o $@ : %g' > $@; \
	[ -s $@ ] || rm -f $@

ifneq ($(MAKECMDGOALS), clean)
-include $(DEPS)
endif