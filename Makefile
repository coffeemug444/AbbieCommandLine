CC=g++
IDIR=..
LDIR=../.OBJECTS
DEPS = $(IDIR)/Abbie/abbie.hpp 
ODIR=.obj

main: main.cpp
	$(CC) -g -march=native -o $@ $^ -I$(IDIR) -L$(LDIR) -ffast-math -fopenmp -labbie -lOpenCL -lchess -lbenBrain -lbenMat

opt: main.cpp
	$(CC) -O3 -march=native -o $@ $^ -I$(IDIR) -L$(LDIR) -ffast-math -fopenmp -labbieOpt -lOpenCL -lchess -lbenBrainOpt -lbenMatOpt
.PHONY: all
all:
	make main
	make opt

.PHONY: clean
clean:
	rm -f $(OBJ) $(OBJ_OPT) main opt
