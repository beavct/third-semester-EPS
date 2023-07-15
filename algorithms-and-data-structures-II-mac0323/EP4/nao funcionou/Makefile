PP=g++
COMPFLAGS= -Wall -ansi -pedantic
OTHERS= regexp.cpp

###################################################################################

OBJS= regexp.o
MAIN= main.cpp

###################################################################################

all: ep

regexp.o: regexp.h

main.o: main.cpp

ep: ${OBJS}
		${PP} ${COMPFLAGS} -o ep4 ${MAIN} ${OTHERS}
		@rm -rf *.o 