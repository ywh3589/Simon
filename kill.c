#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char **argv)
{
  int i = 0;
  int j = 0;
  int numOfArgs = atoi(argv[1]);
  

  if(argc < 2){
    printf(2, "usage: kill pid...\n");
    printf(1, "|\\_/|\n");
    printf(1, "|q p|   /}\n");
    printf(1, "( 0 )\"\"\"\\\n");
    printf(1, "|\"^\"`    |\n");
    printf(1, "||_/=\\\\__|\n");
    printf(2, "Type in other numbers after getting to know pids you want to stop the process with ps command!\n");
    exit();
  }
  else{
    if(i == 1){
        printf(1, "|\\_/|\n");
    printf(1, "|q p|   /}\n");
    printf(1, "( 0 )\"\"\"\\\n");
    printf(1, "|\"^\"`    |\n");
    printf(1, "||_/=\\\\__|\n");
    printf(2, "hey buddy!, can not kill initial process.\n");
    printf(2, "type in other numbers after getting to know pids you want to stop the process with ps command!\n");
     
     }
     else{
      for(j = 1; j < numOfArgs; j++)
        kill(atoi(argv[j]));
     }

  }
  exit();
}
