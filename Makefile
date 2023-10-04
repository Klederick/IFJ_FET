CC=gcc
CFLAGS=-Wall

scanner: scanner.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f scanner