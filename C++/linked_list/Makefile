# Makefile

CC=g++
CFLAGS=-I. -pipe -O2 -std=c++20
DEPS=node.h list.h
OBJS=main.o
EXEC=main

%.o: %.cpp ${DEPS}
	${CC} -c -o $@ $< ${CFLAGS}

${EXEC}: ${OBJS}
	${CC} -o $@ $^ ${CFLAGS}

clean:
	rm -rf ${OBJS} ${EXEC}
