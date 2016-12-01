#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  char *from = argv[1];
  char *to = argv[2];
  int from_size = 0;
  int to_size = 0;
  int i = 0;
  int j;
  //get sizes of each operand
  while ( from[i] != '\0' )
    {
      from_size++;
      i++;
    }
  i = 0;
  while ( to[i] != '\0' )
    {
      to_size++;
      i++;
    }
  //error checking for same size and no duplicates
  if ( from_size != to_size )
    {
      fprintf( stderr, "Arguments must be the same size.\n");
      exit(1);
    }
  i = 0;
  for ( i; i < from_size; i++ )
    {
      for ( j = i+1; j < from_size; j++ )
	{
	  if ( from[i] == from[j] )
	    {
	      fprintf( stderr, "Duplicate elements in arg1.\n" );
	      exit(1);
	    }
	}
    }
  i = 0;
  //doing the actual translation
  char out = getchar();
  while ( out != EOF )
    {
      while ( i < from_size )
	{
	  if ( out == from[i] ) 
	    {
	      out = to[i];
	      break;
	    }
	  i++;
	}
      putchar(out);
      out = getchar();
    }
}
