CFLAGS = -Wall -fpic -coverage -lm -std=c99

test_helpers.o: test_helpers.h test_helpers.c
	gcc -c test_helpers.c -g $(FLAGS)

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittestresults: unittestresults.out

unittestresults.out: test_helpers.o dominion.o rngs.o unittest1.c unittest2.c
	echo "Unit test results -- non-card function tests:" > unittestresults.out

	echo "Unit test 1:" >> unittestresults.out
	gcc -o unittest1 unittest1.c test_helpers.o dominion.o rngs.o $(CFLAGS)
	./unittest1 >> unittestresults.out
	./run_gcov.sh shuffle >> unittestresults.out

	echo "Unit test 2:" >> unittestresults.out
	gcc -o unittest2 unittest2.c test_helpers.o dominion.o rngs.o $(CFLAGS)
	./unittest2 >> unittestresults.out
	./run_gcov.sh fullDeckCount >> unittestresults.out

	echo "Unit test 3:" >> unittestresults.out
	gcc -o unittest3 unittest3.c test_helpers.o dominion.o rngs.o $(CFLAGS)
	./unittest3 >> unittestresults.out
	./run_gcov.sh isGameOver >> unittestresults.out

	echo "Unit test 4:" >> unittestresults.out
	gcc -o unittest4 unittest4.c test_helpers.o dominion.o rngs.o $(CFLAGS)
	./unittest4 >> unittestresults.out
	./run_gcov.sh updateCoins >> unittestresults.out
	#./analyze_gcov.sh "function updateCoins" "function smithy" >> unittestresults.out

	echo "--------------------------------------------------------------------------------" >> unittestresults.out
	echo "Unit test results -- card implementation function tests:" >> unittestresults.out

	echo "Card test 1:" >> unittestresults.out
	gcc -o cardtest1 cardtest1.c test_helpers.o dominion.o rngs.o $(CFLAGS)
	./cardtest1 >> unittestresults.out
	./run_gcov.sh smithy_play >> unittestresults.out

	echo "Card test 2:" >> unittestresults.out
	gcc -o cardtest2 cardtest2.c test_helpers.o dominion.o rngs.o $(CFLAGS)
	./cardtest2 >> unittestresults.out
	./run_gcov.sh PLACEHOLD >> unittestresults.out

	echo "Card test 3:" >> unittestresults.out
	gcc -o cardtest3 cardtest3.c test_helpers.o dominion.o rngs.o $(CFLAGS)
	./cardtest3 >> unittestresults.out
	./run_gcov.sh PLACEHOLD >> unittestresults.out

	echo "Card test 4:" >> unittestresults.out
	gcc -o cardtest4 cardtest4.c test_helpers.o dominion.o rngs.o $(CFLAGS)
	./cardtest4 >> unittestresults.out
	./run_gcov.sh PLACEHOLD >> unittestresults.out

all: playdom player

binaries=unittest1 unittest2 unittest3 unittest4

clean:
	rm -f *.o *.exe $(binaries) playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
