## Makefile

INC_DIR =

ALL_LIBS = -llapack

rootFile = main.cc

readFiles = parser_tab.cc lexyy.cc ParseTree.cc

solverFiles = World.cc Thing.cc Atom.cc Crystal.cc Law.cc Solver.cc EqNewton.cc EqEigen.cc EqAllElectron.cc EqHydrogen.cc

fieldFiles = Field.cc

utilityFiles = utilities.cc numericalsolvers.cc Stopwatch.cc Sparse.cc

inputFile = $(rootFile) $(solverFiles) $(fieldFiles) $(utilityFiles) $(readFiles)

objectFile = $(inputFile:.cc=.o)
dependFile = $(inputFile:.cc=.d)

COMPILE_OPTION =
LINK_OPTION =

default: all

all: $(objectFile)
	g++ $(LINK_OPTION) $(INC_DIR) $(objectFile) $(ALL_LIBS) -o g1st
	rm -f *~

%.o: %.cc
	g++ $(COMPILE_OPTION) $(INC_DIR) -c $< -o $@

%.d: %.cc
	g++ -M $(COMPILE_OPTION) $(INC_DIR) -c $< > $@

-include $(dependFile)

lexyy.cc: scanner.l
	flex scanner.l
	mv lex.yy.c lexyy.cc

parser_tab.cc: parser.y
	bison -d parser.y
	mv parser.tab.c parser_tab.cc
	mv parser.tab.h parser_tab.h

clean:
	rm -f *~
	rm -f *.o
	rm -f *.d
	rm -f lexyy.cc
	rm -f parser_tab.cc
	rm -f parser_tab.h
	rm -f g1st
