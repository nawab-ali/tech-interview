# Makefile

CC=/usr/bin/mpicc
CFLAGS=-I. -pipe -O2
DEPS=
OBJS=hello.o
EXEC=hello

%.o: %.c ${DEPS}
	${CC} -c -o $@ $< ${CFLAGS}

${EXEC}: ${OBJS}
	${CC} -o $@ $^ ${CFLAGS}

clean:
	rm -rf ${OBJS} ${EXEC}
