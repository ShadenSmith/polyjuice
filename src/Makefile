
CC = g++
EXEC = polyjuice
OPTS = -Wall -g

Polyjuice: main.o
	$(CC) -o $(EXEC) $(OPTS) main.o

main.o: main.cc
	$(CC) -c $(OPTS) main.cc

clean:
	rm $(EXEC) *.o
