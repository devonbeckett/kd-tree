CC=gcc
FLAGS=-I./src/ `pkg-config --cflags opencv` -fopenmp
TARGETS=server
LIBS=-lm `pkg-config --libs opencv` -fopenmp

main: $(parem1)


lib/%.o: src/%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(parem1) lib/*.o

%:lib/%.o lib/hw4kd.o lib/kdtree.o
	$(CC) -o $@ $^ $(LIBS)
