CFLAGS = -Wall -fpic -coverage -lm



all: playdom player testDrawCard testBuyCard badTestDrawCard
	$(info ******** testing all *******)
  
rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)
  $(info ******** compiling rngs.o *******)
  
dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)
	$(info ******** compiling dominion.o *******)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
	$(info ******** compiling playdom *******)
  
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)
	$(info ******** compiling testDrawCard *******)
  
badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)
	$(info ******** compiling badTestDrawCard *******)
  
testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)
	$(info ******** compiling testBuyCard *******)
  
testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)
	$(info ******** compiling testAll *******)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)
	$(info ******** compiling interface.o *******)
  
runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	$(info ******** compiling runtests *******)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)
	$(info ******** compiling player *******)

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
<<<<<<< HEAD
	$(info ******** clean2 is on *******)
=======
	$(info ******** clean is off now *******)
>>>>>>> c83b829ae04270fdf5ef49986f1f414f642fedf5
