PP=g++
COMPFLAGS= -Wall -g -O2
OTHERS= digraph.cpp

###################################################################################

OBJS = digraph.h
MAIN=main.cpp

###################################################################################

all: ep

digraph.o: digraph.h

main.o: main.cpp

ep: ${OBJS}
		${PP} ${COMPFLAGS} -o ep3 ${MAIN} ${OTHERS}
		@rm -rf *.o 