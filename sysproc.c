#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"


int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int 
sys_random(void)
{
    int seed;
   if(argint(0, &seed) < 0)
    return -1;
    return random(seed);

}
int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_cps(void)
{
  char *opt;
  
  if(argstr(0, &opt) < 0) {
    return -1;
  } else {
    if (!strncmp("-l", opt, 2)) {
      return cps(1);
    } else {
      return cps(0);
    }
  }
  return -1;
    
}

int
sys_renice(void)
{
  int pid;
  int pri;

  if (argint(0, &pid) < 0) {
    return -1;
  }

  if (argint(1, &pri) < 0) {
    return -1;
  }

  if (pid < 0) {
    return -1;
  }

  if (pri < -20) {
    pri = -20;
  } else if (pri > 19) {
    pri = 19;
  }

  return renice(pid, pri);
    
}
