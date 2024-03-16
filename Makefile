CC=gcc
CFLAGS=-g -o
OBJETS=gamain.c ga.c

ga:$(OBJETS)
	$(CC) $(CFLAGS) $@ $^
	./ga

test:
	./ga


clean:
	rm ga