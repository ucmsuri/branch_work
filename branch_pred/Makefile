CC = g++
CCFLAGS = -static -g -std=c++0x

predictor: main.o predictor.o
	${CC} ${CCFLAGS}  main.o predictor.o -o predictor


main.o: main.c  predictor.h
	${CC} ${CCFLAGS} -c main.c


predictor.o: predictor.c predictor.h 
	${CC} ${CCFLAGS} -c predictor.c

clean:
	rm -f *.o predictor
