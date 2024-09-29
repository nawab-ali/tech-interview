##Makefile for SAXPY CUDA code

CC=/usr/local/cuda/bin/nvcc
CFLAGS=-I.
DEPS=
EXEC=saxpy
OBJ=saxpy.o

%.o: %.cu ${DEPS}
	${CC} -c -o $@ $< ${CFLAGS}

${EXEC}: ${OBJ}
	${CC} -o $@ $^ ${CFLAGS}

clean:
	rm -rf ${OBJ} ${EXEC}
