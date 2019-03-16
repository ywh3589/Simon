#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char **argv)
{
  int seed = 1;
  int i = 0;
    for(i = 0; i < 10; i++){
    int randomNum = random(seed);
    seed = randomNum;
    printf(1, "#%dth random number is %d\n", i, randomNum);
    }
  exit();
}
