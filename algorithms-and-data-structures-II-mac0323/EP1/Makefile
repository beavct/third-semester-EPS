PP=g++
COMPFLAGS= -Wall
OTHERS= file.cpp plane.cpp priorityQueue.cpp randomGenerator.cpp runway.cpp

###################################################################################

OBJS = file.o plane.o priorityQueue.o randomGenerator.o runway.o
MAIN=main.cpp

###################################################################################

all: ep

file.o: file.h
plane.o: plane.h
priorityQueue.o: priorityQueue.h
randomGenerator.o: randomGenerator.h
runway.o: runway.h

main.o: main.cpp

ep: ${OBJS}
		${PP} ${COMPFLAGS} -o ep1 ${MAIN} ${OTHERS}
		@rm -rf *.o 
