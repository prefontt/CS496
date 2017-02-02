CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

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

unittests: unittest1.c unittest2.c unittest3.c unittest4.c dominion.c dominion.h
	gcc -o unittest1 unittest1.c dominion.c rngs.c $(CFLAGS)
	gcc -o unittest2 unittest2.c dominion.c rngs.c $(CFLAGS)
	gcc -o unittest3 unittest3.c dominion.c rngs.c $(CFLAGS)
	gcc -o unittest4 unittest4.c dominion.c rngs.c $(CFLAGS)

cardtests: cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.c dominion.h
	gcc -o cardtest1 -g cardtest1.c dominion.c rngs.c $(CFLAGS)
	gcc -o cardtest2 -g cardtest2.c dominion.c rngs.c $(CFLAGS)
	gcc -o cardtest3 -g cardtest3.c dominion.c rngs.c $(CFLAGS)
	gcc -o cardtest4 -g cardtest4.c dominion.c rngs.c $(CFLAGS)

unittestresults.out: cardtests unittests
	./cardtest1
	./cardtest2
	./cardtest3
	./cardtest4
	./unittest1
	./unittest2
	./unittest3
	./unittest4
	gcov cardtest1.c > unittestresults.out
	gcov cardtest2.c >> unittestresults.out
	gcov cardtest3.c >> unittestresults.out
	gcov cardtest4.c >> unittestresults.out
	gcov unittest1.c >> unittestresults.out
	gcov unittest2.c >> unittestresults.out
	gcov unittest3.c >> unittestresults.out
	gcov unittest4.c >> unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so badTestDrawCard testDrawCard
