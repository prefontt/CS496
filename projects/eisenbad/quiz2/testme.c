/* Author of inputString and inputChar: Daniel Eisenbach
   Date: 2/5/17
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
  // create array of possible char values
  char testChars[] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']'};
	
	
  return testChars[rand() % sizeof(testChars)];
}

char *inputString()
{
  // create array of possible char values for building string
  char strChars[] = {'r', 'e', 's', 't'};
  char *testStr = malloc(sizeof(char) * 5);
	
      
  // select array of characters using rand
  int i;
  for (i = 0; i < 5; i++) {testStr[i] = strChars[rand() % sizeof(strChars)];}
  testStr[5] = '\0';
	
  return testStr;
}

void testme()
{
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
      printf("\nerror \n");
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
