CFLAGS = -Wall -lm -std=c99 -coverage -fpic
BINARIES = testme

default:
	gcc -o testme testme.c $(CFLAGS)

clean:
	rm -f *.o *.exe $(BINARIES) *.gcov *.gcda *.gcno
