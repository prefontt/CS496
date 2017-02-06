#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // Generates a random ASCII printable character (32 - 126)
    return (rand() % 95) + 32;
}

char *inputString()
{
    const char lower_case_char_set[] = "rest"; // set the char_set to change testing time and chars covered.
    int len = 6;
    const int char_set_size = sizeof(lower_case_char_set) - 1;
    char *randomString = malloc(len * sizeof(char));
    int i;
    for (i = 0; i < len - 1; i++){
      int key = rand() % char_set_size;
      randomString[i] = lower_case_char_set[key];
    }
    randomString[len] = '\0';
    return randomString;
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
