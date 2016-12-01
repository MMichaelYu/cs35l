#include "randcpuid.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

/* Main program, which outputs N bytes of random data.  */
int
main (int argc, char **argv)
{
  /* Check arguments.  */
  bool valid = false;
  long long nbytes;
  if (argc == 2)
    {
      char *endptr;
      errno = 0;
      nbytes = strtoll (argv[1], &endptr, 10);
      if (errno)
	perror (argv[1]);
      else
	valid = !*endptr && 0 <= nbytes;
    }
  if (!valid)
    {
      fprintf (stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
      return 1;
    }

  /* If there's no work to do, don't worry about which library to use.  */
  if (nbytes == 0)
    return 0;

  /* Now that we know we have work to do, arrange to use the
     appropriate library.  */
  void (*initialize) (void);
  unsigned long long (*rand64) (void);
  void* message;
  void (*finalize) (void);
  if (rdrand_supported ())
    {
      message = dlopen("randlibhw.so", RTLD_NOW);
      if(!message)
	{
	  fprintf(stderr, "dlopen error");
	  exit(1);
	}
      initialize = dlsym(message, "hardware_rand64_init");
      rand64 = dlsym(message, "hardware_rand64");
      finalize = dlsym(message, "hardware_rand64_fini");
      if (initialize == NULL || rand64 == NULL || finalize == NULL)
	{
	  fprintf(stderr, "dlsym error");
	  exit(1);
	}
      printf("HW\n");
      //finalize = hardware_rand64_fini;
    }
  else
    {
      //initialize = software_rand64_init;
      //rand64 = software_rand64;
      //finalize = software_rand64_fini;
      message = dlopen("randlibsw.so", RTLD_NOW);
      if (!message)
	{
	  fprintf(stderr, "dlopen error");
	  exit(1);
	}
      initialize = dlsym(message, "software_rand64_init");
      rand64 = dlsym(message, "software_rand64");
      finalize = dlsym(message, "software_rand64_fini");
      if (initialize == NULL || rand64 == NULL || finalize == NULL)
	{
	  fprintf(stderr, "dlsym error");
	  exit(1);
	}
      printf("SW\n");
    }

  //initialize ();
  int wordsize = sizeof rand64 ();
  int output_errno = 0;

  do
    {
      unsigned long long x = rand64 ();
      size_t outbytes = nbytes < wordsize ? nbytes : wordsize;
      //if (fwrite (&x, 1, outbytes, stdout) != outbytes)
      if (printf("%llu\n",x) == 0)
	{
	  output_errno = errno;
	  break;
	}
      nbytes -= outbytes;
    }
  while (0 < nbytes);

  if (fclose (stdout) != 0)
    output_errno = errno;

  if (output_errno)
    {
      errno = output_errno;
      perror ("output");
      //finalize ();
      return 1;
    }

  //finalize ();
  dlclose(message);
  return 0;
}