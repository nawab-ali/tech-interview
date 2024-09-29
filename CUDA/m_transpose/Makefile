## Makefile

CC=/usr/local/cuda/bin/nvcc
DEP=
CFLAGS=-I.
OBJ=m_transpose.o
EXEC=m_transpose

%.o: %.cu ${DEP}
	${CC} -c -o $@ $< ${CFLAGS}

${EXEC}: ${OBJ}
	${CC} -o $@ $^ ${CFLAGS}

clean:
	rm -rf ${OBJ} ${EXEC}
