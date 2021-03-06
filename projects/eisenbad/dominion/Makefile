CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

betterTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o betterTestDrawCard -g  betterTestDrawCard.c dominion.o rngs.o $(CFLAGS)

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
	gcc -o unittest1 -g unittest1.c dominion.c rngs.c $(CFLAGS)
	gcc -o unittest2 -g unittest2.c dominion.c rngs.c $(CFLAGS)
	gcc -o unittest3 -g unittest3.c dominion.c rngs.c $(CFLAGS)
	gcc -o unittest4 -g unittest4.c dominion.c rngs.c $(CFLAGS)

cardtests: cardtest1.c cardtest2.c cardtest3.c cardtest4.c testfuncs.c dominion.c dominion.h
	gcc -o cardtest1 -g cardtest1.c dominion.c rngs.c testfuncs.c $(CFLAGS)
	gcc -o cardtest2 -g cardtest2.c dominion.c rngs.c testfuncs.c $(CFLAGS)
	gcc -o cardtest3 -g cardtest3.c dominion.c rngs.c testfuncs.c $(CFLAGS)
	gcc -o cardtest4 -g cardtest4.c dominion.c rngs.c testfuncs.c $(CFLAGS)

unittestresults.out: unittests cardtests
	./cardtest1 > unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	./unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov -b -f cardtest1.c >> unittestresults.out
	echo ---------- >> unittestresults.out
	gcov -b -f cardtest2.c >> unittestresults.out
	echo ---------- >> unittestresults.out
	gcov -b -f cardtest3.c >> unittestresults.out
	echo ---------- >> unittestresults.out
	gcov -b -f cardtest4.c >> unittestresults.out
	echo ---------- >> unittestresults.out
	gcov -b -f unittest1.c >> unittestresults.out
	echo ---------- >> unittestresults.out
	gcov -b -f unittest2.c >> unittestresults.out
	echo ---------- >> unittestresults.out
	gcov -b -f unittest3.c >> unittestresults.out
	echo ---------- >> unittestresults.out
	gcov -b -f unittest4.c >> unittestresults.out
	echo ---------- >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	echo ---------- >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out  

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o *.c~ *~ unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 betterTestDrawCard playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
