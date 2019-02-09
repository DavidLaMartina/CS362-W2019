CFLAGS = -Wall -lm -std=c99 -coverage -fpic
BINARIES = testme

default:
	gcc -o testme testme.c $(CFLAGS)
	./testme

gcov:
	gcov testme.c -f -b

clean:
	rm -f *.o *.exe $(BINARIES) *.gcov *.gcda *.gcno
