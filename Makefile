CC=gcc
FLAGS=-I./src/ `pkg-config --cflags opencv` -fopenmp
TARGETS=hw4kdex
LIBS=-lm `pkg-config --libs opencv` -fopenmp

main: $(TARGETS)


lib/%.o: src/%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(TARGETS) lib/*.o

%:lib/%.o lib/hw4kd.o lib/kdtree.o
	$(CC) -o $@ $^ $(LIBS)
