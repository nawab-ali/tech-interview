##Makefile for vector dot product in CUDA

CC=/usr/local/cuda/bin/nvcc
CFLAGS=-I.
DEP=
OBJ=v_dot_prod.o
EXEC=v_dot_prod

%.o: %.cu ${DEP}
	${CC} -c -o $@ $< ${CFLAGS}

${EXEC}: ${OBJ}
	${CC} -o $@ $^ ${CFLAGS}

clean:
	rm -rf ${OBJ} ${EXEC}
