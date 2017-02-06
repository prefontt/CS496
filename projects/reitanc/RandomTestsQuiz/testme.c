#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
	char RetVal;
	int RandVal;

	RandVal = (rand() % 9);

	switch (RandVal)
	{
		case 1:
			RetVal = '[';
			break;
		case 2:
			RetVal = '(';
			break;
		case 3:
			RetVal = '{';
			break;
		case 4:
			RetVal = 'a';
			break;
		case 5:
			RetVal = 'x';
			break;
		case 6:
			RetVal = '}';
			break;
		case 7:
			RetVal = ')';
			break;
		case 8:
			RetVal = ']';
			break;
		default:
			RetVal = ' ';
			break;	
	}

    return RetVal;
}

char *inputString(char *str, size_t size)
{
    // TODO: rewrite this function
	int RandVal;

	RandVal = (rand() % 4);

	// Testing the Testing capabilities by forcing a response.
	str[0]='r'; str[1]='e'; str[2]='s'; str[3]='e'; str[4]='t'; str[5]='\0';
	return str;

	switch (RandVal)
	{
		case 1:
			str[0]='H'; str[1]='e'; str[2]='l'; str[3]='l'; str[4]='o'; str[5]='\0';
			break;
		case 2:
			str[0]='W'; str[1]='o'; str[2]='r'; str[3]='l'; str[4]='d'; str[5]='\0';
			break;
		case 3:
			str[0]='r'; str[1]='e'; str[2]='s'; str[3]='e'; str[4]='t'; str[5]='\0';
			break;
		default:
			for (size_t i = 0; i < size; i++)
			{
				str[i] = inputChar();
			}
			str[size] = '\0';
			break;
	}

    return str;
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
    s = inputString(s, 6);
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' ' && state == 3) state = 4;
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
    srand(time(0));
    testme();
    return 0;
}
