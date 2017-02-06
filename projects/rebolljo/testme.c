/*
CS362-400
02/05/2017
Joseph Rebolledo
Random Testing Quiz 2
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{

    return ((rand() % 95) + 32);//Return a value between 32 and 126; From the ascii table this is SPACE to ~
}

char *inputString()
{
   static char returnString[6]; //5 characters plus the terminating null character

   int i = 0;
   
   int j = rand() % 1000;//Assign j a random value so the program can randomly decide to pass the string needed to print the corresponding message and  exit the program

   if(j == 1){//Return the needed word to print the error message and exit the program
      returnString[0] = 'r';
      returnString[1] = 'e';
      returnString[2] = 's';
      returnString[3] = 'e';
      returnString[4] = 't';
      returnString[5] = '\0';
    }
  else{

     for(i; i < 5; i++){
        returnString[i] = rand() % 97 + 26;//Place random character: a-z
     }

     returnString[5] = '\0'; //Place terminating null character at end of string
    }


    return returnString;
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
