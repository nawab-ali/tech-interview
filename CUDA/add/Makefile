##Makefile

CC=/usr/local/cuda/bin/nvcc
CFLAGS=-I.
DEPS=
OBJ=add.o
EXEC=add

%.o: %.cu $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	\rm -rf $(EXEC) $(OBJ)
