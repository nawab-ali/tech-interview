## Makefile for adding 2 matrices on GPU

CC=/usr/local/cuda/bin/nvcc
DEP=
CFLAGS=-I.
OBJ=m_add.o
EXEC=m_add

%.o: %.cu ${DEP}
	${CC} -c -o $@ $< ${CFLAGS}

${EXEC}: ${OBJ}
	${CC} -o $@ $^ ${CFLAGS}

clean:
	rm -rf ${OBJ} ${EXEC}
