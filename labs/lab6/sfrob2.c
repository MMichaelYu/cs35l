#include <stdio.h>
#include <stdlib.h>

int frobcmp_count = 0;

int frobcmp(char const * a, char const * b)
{
  frobcmp_count += 1;
  while (( *a != 32 ) && ( *b != 32 ))
    {
      if (( *a^42 ) < ( *b^42 )) {return -1;}
      else if (( *a^42 ) > ( *b^42 )) {return 1;}
      a++;
      b++;
    }
  //a and b are equal
  if (( *a == 32 ) && ( *b == 32 )) {return 0;}
  //a is the prefix of b
  if (( *a == 32 ) && ( *b != 32 )) {return -1;}
  //b is the prefix of a
  return 1;
}

int frobcmp_casted(const void * a, const void * b)
{
  return frobcmp( *(char const **)a, *(char const **)b );
}

int main()
{
  int mem = 100;
  char* input = (char*)malloc(sizeof(char) * mem);
  if (input == NULL)
    {
      fprintf(stderr, "Memory allocation error.");
      exit(1);
    }
  int ch;
  int i;
  int word_count = 0;
  for ( i = 0; ( ch = getchar() ) != EOF; i++ )
    {
      if ( i == mem )
    {
      mem = mem * 2;
      input = (char*)realloc(input, mem);
      if (input == NULL)
        {
          fprintf(stderr, "Memory reallocation error.");
          exit(1);
        }
    }

      if ( ch == ' ' ) {word_count++;}
      input[i] = ch;
    }

  if ( input[i-1] != ' ' )
    {
      input[i] = ' ';
      word_count++;
    }

  int input_size = i;

  char **store_strings = (char**)malloc(sizeof(char*)*word_count);

  if ( store_strings == NULL )
    {
      fprintf(stderr, "Memory allocation error.");
      exit(1);
    }

  char *traverse = input;
  int j;
  for ( j = 0; j < word_count; j++ )
    {
      store_strings[j] = traverse;
      if ( j == (word_count - 1) ) {break;}

      while ( *traverse != ' ' ) {traverse++;}
      traverse++;
    }

  qsort(store_strings, word_count, sizeof(char*), frobcmp_casted);

  int k;
  char *ptr;
  for ( k = 0; k < word_count; k++)
    {
      ptr = store_strings[k];
      putchar(*ptr);
      while ( *ptr != ' ')
    {
      ptr++;
      putchar(*ptr);
    }
    }
  fprintf(stderr, "Comparisons: %d\n", frobcmp_count);
  free(store_strings);
  free(input);
  exit(0);
}
