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
	
unittest1:
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -g -std=c99 -o unittest1 -g unittest1.c dominion.h dominion.c rngs.h rngs.c
	
unittest2:
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -g -std=c99 -o unittest2 -g unittest2.c dominion.h dominion.c rngs.h rngs.c

unittest3:
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -g -std=c99 -o unittest3 -g unittest3.c dominion.h dominion.c rngs.h rngs.c
	
unittest4:
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -g -std=c99 -o unittest4 -g unittest4.c dominion.h dominion.c rngs.h rngs.c

cardtest1:
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -g -std=c99 -o cardtest1 -g cardtest1.c dominion.h dominion.c rngs.h rngs.c
	
cardtest2:
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -g -std=c99 -o cardtest2 -g cardtest2.c dominion.h dominion.c rngs.h rngs.c

cardtest3:
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -g -std=c99 -o cardtest3 -g cardtest3.c dominion.h dominion.c rngs.h rngs.c

cardtest4:
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -g -std=c99 -o cardtest4 -g cardtest4.c dominion.h dominion.c rngs.h rngs.c

unittestresults.out:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest1.c rngs.c -o unittest1 -lm -g
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest2.c rngs.c -o unittest2 -lm -g
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest3.c rngs.c -o unittest3 -lm -g
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest4.c rngs.c -o unittest4 -lm -g
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest1.c rngs.c -o cardtest1 -lm -g
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest2.c rngs.c -o cardtest2 -lm -g
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest3.c rngs.c -o cardtest3 -lm -g
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest4.c rngs.c -o cardtest4 -lm -g
	./unittest1 &> unittestresult.out
	gcov unittest1.c >> unittestresult.out
	./unittest2 >> unittestresult.out
	gcov unittest2.c >> unittestresult.out
	./unittest3 >> unittestresult.out
	gcov unittest3.c >> unittestresult.out
	./unittest4 >> unittestresult.out
	gcov unittest4.c >> unittestresult.out
	./cardtest1 >> unittestresult.out
	gcov cardtest1.c >> unittestresult.out
	./cardtest2 >> unittestresult.out
	gcov cardtest2.c >> unittestresult.out
	./cardtest3 >> unittestresult.out
	gcov cardtest3.c >> unittestresult.out
	./cardtest4 >> unittestresult.out
	gcov cardtest4.c >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	
coverage:
	make clean
	make unit1
	./unittest1
	gcov dominion.c &> coverage.out

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 testInit testInit.exe *.gcov *.gcda *.gcno *.so
