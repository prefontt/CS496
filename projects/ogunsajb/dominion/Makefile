CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

refactor.o: dominion.h refactor.h refactor.c 
	gcc -c refactor.c -g   $(CFLAGS)

dominion.o: dominion.h refactor.h dominion.c rngs.o
	gcc -c dominion.c refactor.c -g   $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o  refactor.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o  refactor.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o refactor.o  rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o refactor.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o  refactor.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o  refactor.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o refactor.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o  refactor.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o refactor.o  rngs.o interface.o $(CFLAGS)

unittest1: unittest1.c dominion.o refactor.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o refactor.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o refactor.o rngs.o
	gcc -o unittest2 -g  unittest2.c dominion.o refactor.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o refactor.o rngs.o
	gcc -o unittest3 -g  unittest3.c dominion.o refactor.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o refactor.o rngs.o
	gcc -o unittest4 -g  unittest4.c dominion.o refactor.o rngs.o $(CFLAGS)
	
cardtest1: cardtest1.c dominion.o refactor.o rngs.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o refactor.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o refactor.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o refactor.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o refactor.o rngs.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o refactor.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o refactor.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o refactor.o rngs.o $(CFLAGS)
	
unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4	
	./unittest1 &> unittestresults.out	
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out	
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	gcov refactor.c >> unittestresults.out
	cat refactor.c.gcov >> unittestresults.out

all: playdom player testDrawCard testBuyCard badTestDrawCard unittestresults.out
	
clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 badTestDrawCard testDrawCard *.gcov *.gcda *.gcno *.so *.out 
