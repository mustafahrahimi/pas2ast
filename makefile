cc = gcc
CFLAGS = -Wall

parser: driver.c parser.c
	$(cc) $(CFLAGS) -o parser driver.c parser.c

clean:
	rm -f parser
