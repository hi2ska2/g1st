## Makefile

default: all

inputFile = main.cc

objectFile = $(inputFile:.cc=.o)
dependFile = $(inputFile:.cc=.d)

COMPILE_OPTION =
LINK_OPTION =

all: $(objectFile)
	g++ $(LINK_OPTION) $(INC_DIR) $(objectFile) $(ALL_LIBS) -o g1st
	rm -f *~

%.o: %.cc
	g++ $(COMPILE_OPTION) $(INC_DIR) -c $< -o $@

%.d: %.cc
	g++ -M $(COMPILE_OPTION) $(INC_DIR) -c $< > $@

clean:
	rm -f *~
	rm -f *.o
	rm -f *.d
	rm -f g1st
