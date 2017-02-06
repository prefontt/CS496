#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    //restrict input domain to those characters used in the testme() function

	int select = rand() % 9;
	
	switch (select) {
	case 0:
	return '[';
	case 1:
	return '(';
	case 2:
	return '{';
	case 3:
	return ' ';
	case 4:
	return 'a';
	case 5:
	return 'x';
	case 6:
	return '}';
	case 7:
	return ')';
	case 8:
	return ']';
	}
}

char *inputString()
{
    	//i'm tempted to just have this function return 'reset'
	// but we have to have *some* semblence of random
	// so let's just restrict the domain to one of three possible choices

	int select = rand() % 3;

	switch 	(select){
	case 0:
	return "blorp";
	case 1:
	return "badoo";
	case 2:
	return "reset";
	}
}

void testme()
{
  srand(time(NULL)); //initializing srand here because initializing it inside the
			//functions makes the program take forever (returns would change only once per second)
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
