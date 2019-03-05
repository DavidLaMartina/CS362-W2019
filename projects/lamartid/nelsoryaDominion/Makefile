CFLAGS= -Wall -fpic -coverage -lm -std=c99 -g3
GFLAGS = -Wall -fpic -coverage -lm -std=c99 -g3

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

unittestresults.out: test_helpers.c dominion.c rngs.c
	echo "Unit test results -- non-card function tests:" > unittestresults.out

	echo "\nUnit test 1:" >> unittestresults.out
	gcc -o unittest1 unittest1.c test_helpers.c dominion.c rngs.c $(GFLAGS)
	./unittest1 >> unittestresults.out
	./run_gcov.sh shuffle >> unittestresults.out
	#./analyze_gcov.sh "function shuffle" "function playCard" >> unittestresults.out

	echo "\nUnit test 2:" >> unittestresults.out
	gcc -o unittest2 unittest2.c test_helpers.c dominion.c rngs.c $(GFLAGS)
	./unittest2 >> unittestresults.out
	./run_gcov.sh fullDeckCount >> unittestresults.out

	echo "\nUnit test 3:" >> unittestresults.out
	gcc -o unittest3 unittest3.c test_helpers.c dominion.c rngs.c $(GFLAGS)
	./unittest3 >> unittestresults.out
	./run_gcov.sh isGameOver >> unittestresults.out

	echo "\nUnit test 4:" >> unittestresults.out
	gcc -o unittest4 unittest4.c test_helpers.c dominion.c rngs.c $(GFLAGS)
	./unittest4 >> unittestresults.out
	./run_gcov.sh updateCoins >> unittestresults.out
	#./analyze_gcov.sh "function updateCoins" "function smithy" >> unittestresults.out

	echo "\n--------------------------------------------------------------------------------" >> unittestresults.out
	echo "Unit test results -- card implementation function tests:" >> unittestresults.out

	echo "\nCard test 1:" >> unittestresults.out
	gcc -o cardtest1 cardtest1.c test_helpers.c dominion.c rngs.c $(GFLAGS)
	./cardtest1 >> unittestresults.out
	./run_gcov.sh smithyEffect >> unittestresults.out

	echo "\nCard test 2:" >> unittestresults.out
	gcc -o cardtest2 cardtest2.c test_helpers.c dominion.c rngs.c $(GFLAGS)
	./cardtest2 >> unittestresults.out
	./run_gcov.sh adventureEffect >> unittestresults.out

	echo "\nCard test 3:" >> unittestresults.out
	gcc -o cardtest3 cardtest3.c test_helpers.c dominion.c rngs.c $(GFLAGS)
	./cardtest3 >> unittestresults.out
	./run_gcov.sh villageEffect >> unittestresults.out

	echo "\nCard test 4:" >> unittestresults.out
	gcc -o cardtest4 cardtest4.c test_helpers.c dominion.c rngs.c $(GFLAGS)
	./cardtest4 >> unittestresults.out
	./run_gcov.sh council_roomEffect >> unittestresults.out

randomtest: randomtestcard1.out randomtestcard2.out randomtestadventurer.out

randomtestcard1.out: test_helpers.c dominion.c rngs.c
	echo "Random test results for Village:" > randomtestcard1.out
	gcc -o randomtestcard1 randomtestcard1.c test_helpers.c dominion.c rngs.c $(GFLAGS)
	./randomtestcard1 >> randomtestcard1.out
	./run_gcov.sh villageEffect >> randomtestcard1.out

randomtestcard2.out: test_helpers.c dominion.c rngs.c
	echo "Random test results for Council Room:" > randomtestcard2.out
	gcc -o randomtestcard2 randomtestcard2.c test_helpers.c dominion.c rngs.c $(GFLAGS)
	./randomtestcard2 >> randomtestcard2.out
	./run_gcov.sh council_roomEffect >> randomtestcard2.out

randomtestadventurer.out: test_helpers.c dominion.c rngs.c
	echo "Random test results for Adventurer:" > randomtestadventurer.out
	gcc -o randomtestadventurer randomtestadventurer.c test_helpers.c dominion.c rngs.c $(GFLAGS)
	./randomtestadventurer >> randomtestadventurer.out
	./run_gcov.sh adventureEffect >> randomtestadventurer.out

all: playdom player

binaries=unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer randomtestcard1 randomtestcard2

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe $(binaries)
