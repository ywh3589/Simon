#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char **argv)
{
  int i, j;
  int numOfArgs = argc;

  i = atoi(argv[1]);
  
  if(argc < 2){
    printf(2, "usage: kill pid...\n");
    exit();
  }
  else{
    if(i == 1){
        printf(2, "can not kill initial process\n");
      
     }
     else{
     for(j = 1; j < numOfArgs; j++)  
        kill(atoi(argv[j]));
     }

  }
  exit();
}
