#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    /*
    // Random selection of 'actual' characters, from SPACE to ~
    char space = ' ';
    int last_ascii = 127;
    int range = last_ascii - space;
    return ' ' + (rand() % range);
    */

    // Random selection of one of the 9 characters required to progress the
    // state from 0 to 9
    char possible_chars[] = {
    '[','(','{',' ','a','x','}',')',']'};
    int size = 9;
    int idx = rand() % size;
    return possible_chars[idx];
}

char *inputString()
{
    char possible_chars[5] = {'r','e','s','t','\0'};
    int possible_size = 5;

    //const char LOW_CHAR = '\0';
    //const char HIGH_CHAR = '~';

    //int str_len = 5;
    //int str_len = 1 + (rand() % MAX_LENGTH);
    //char *input = malloc(sizeof(char) * str_len);
    static char input[6];

    int idx;
    for (int i = 0; i < 6; i++){
        idx = rand() % possible_size;
        input[i] = possible_chars[idx];
    }
    //char last_char = LOW_CHAR + (rand() % (HIGH_CHAR - LOW_CHAR));
    //input[5] = last_char;
    /*
    for (int i = 0; i < str_len; i++){
        input[i] = LOW_CHAR + (rand() % (HIGH_CHAR - LOW_CHAR));
    }
    */
    return input;
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
       && s[4] == 't' && s[5] == '\0'       // s[5] == '\0' will always be satisfied
       && state == 9)                       // if the string is 5 'actual' characters
    {
      printf("error \n");
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
