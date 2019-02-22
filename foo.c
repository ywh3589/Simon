#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(int argc, char *argv[])
{
  int pid, nthPrime = 1;

  if(argc < 2) {
      printf(2, "Usage: foo [1-1000000] \n");
      exit();
  } else {
    nthPrime = atoi(argv[1]);
    if (nthPrime < 0 || nthPrime > 1000000) {
      printf(2, "Usage: foo [1-1000000] \n");
      exit();
    }
  }

  pid = fork();

  if(pid < 0) {
    exit();
  } else if (pid == 0) {
    // a slow prime number generator for scheduler testing
    // https://stackoverflow.com/questions/13001578/i-need-a-slow-c-sharp-function
    int count = 0;
    int a = 2;
    while (count < nthPrime) {
      int b = 2;
      int p = 1;
      while (b * b <= a) {
        if (a % b == 0) {
          p = 0;
          break;
        }
        b++;
      }
      if (p > 0) {
        count++;
      }
      a++;
    }
    printf(1, "%d\n", --a);
  }

  wait();

  exit();
}
