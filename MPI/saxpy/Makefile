# Makefile

CC=/usr/bin/mpicc
CFLAGS=-I. -pipe -O2
DEPS=
OBJS=saxpy.o
EXEC=saxpy

%.o: %.c ${DEPS}
	${CC} -c -o $@ $< ${CFLAGS}

${EXEC}: ${OBJS}
	${CC} -o $@ $^ ${CFLAGS}

clean:
	rm -rf ${OBJS} ${EXEC}
