PP=g++
COMPFLAGS= -Wall
OTHERS= VO.cpp ABB.cpp TR.cpp ARN.cpp A23.cpp

###################################################################################

OBJS = VO.o ABB.o TR.o ARN.o A23.o
MAIN=main.cpp

###################################################################################

all: ep

VO.o: VO.h
ABB.o: ABB.h
TR.o: TR.h
ARN.o: ARN.h
A23.o: A23.h

main.o: main.cpp

ep: ${OBJS}
		${PP} ${COMPFLAGS} -o ep2 ${MAIN} ${OTHERS}
		@rm -rf *.o 