//Dominic Giacoppe, SF2, unit test 4
//tests compare
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "rngs.h"
#include <string.h>
void aborttest(char * msg)
{
printf("%s\n", msg);
exit(1);
//this func just prints things for me
}

int main()
{
int x = 12;
int y = 13;
char[5] a;
char[5] b;
	
if(compare(&x, &y) != -1)
	aborttest("Compare didn't compare ints right, unittest4");
strcpy(a, "hat");
strcpy(b, "bat");
if(compare(a, b) != 1)
	aborttest("Compare didn't compare strings 1 right, unittest4");
if(compare(b, a) != -1)
	aborttest("Compare didn't compare strings 2 right, unittest4");
strcpy(a, "bat");
if(compare(b, a) != 0)
	aborttest("Compare didn't compare strings 3 right, unittest4");
return 0;
}
