#include "types.h"
#include "stat.h"
#include "user.h"
#include "uspinlock.h"

struct shm_cnt {
  struct uspinlock lock;
  int cnt;
};

int main(int argc, char *argv[])
{
  int pid;
  int i = 0;
  struct shm_cnt *counter;

  pid = fork();
  sleep(1);

  //shm_open: first process will create the page, the second will just attach to the same page
  //we get the virtual address of the page returned into counter
  //which we can now use but will be shared between the two processes
  
  shm_open(1,(char **)&counter);

  for (i = 0; i < 10000; i++) {
    uacquire(&(counter->lock));

    counter->cnt++;

    urelease(&(counter->lock));
  }

  if (pid) {
    printf(1,"Counter in parent is %d\n",counter->cnt);
    wait();
  } else {
    printf(1,"Counter in child is %d\n\n",counter->cnt);
  }

  shm_close(1);
  exit();
  
  return 0;
}
