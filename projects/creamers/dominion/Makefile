CFLAGS = -Wall -fpic -coverage -lm -std=gnu99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

unittest1: unittest1.c dominion.o devassert.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o devassert.o $(CFLAGS)
    
unittest2: unittest2.c dominion.o devassert.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o devassert.o $(CFLAGS)

unittest3: unittest3.c dominion.o devassert.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o devassert.o $(CFLAGS)
    
unittest4: unittest4.c dominion.o devassert.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o devassert.o $(CFLAGS)
    
devassert.o: devassert.h devassert.c
	gcc -c devassert.c -g $(CFLAGS)

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

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)
    
all: playdom player testDrawCard testBuyCard badTestDrawCard unittest1 unittest2 unittest3 unittest4

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
