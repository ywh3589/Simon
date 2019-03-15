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
sys_waitpid(void)
{
    int pid; 
    if(argint(0, &pid) <0)
      return -1;
    return waitpid(pid);
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

int 
sys_pwd(void){

    return pwd();

}

// shared memory

int
sys_shm_open(void)
{
  int id;
  char **pointer;

  if(argint(0, &id) < 0) {
    return -1;
  }

  if(argptr(1, (char **) (&pointer),4)<0) {
    return -1;
  }

  return shm_open(id, pointer);
}

int
sys_shm_close(void)
{
  int id;

  if(argint(0, &id) < 0) {
    return -1;
  }

  return shm_close(id);
}

// semaphores

int
sys_sem_init(void)
{
  struct semaphore * sem;
  int i;
  argptr(0, (char **) &sem, sizeof(struct semaphore*));
  argint(1, &i);
  sem_init(sem, i);
  return 0;
}

int
sys_sem_wait(void)
{
  struct semaphore * sem;
  argptr(0, (char **) &sem, sizeof(struct semaphore*));
  sem_wait(sem);
  return 0;
}

int
sys_sem_signal(void)
{
  struct semaphore * sem;
  argptr(0, (char **) &sem, sizeof(struct semaphore*));
  sem_signal(sem);
  return 0;
}

int
sys_sem_broadcast(void)
{
  struct semaphore * sem;
  argptr(0, (char **) &sem, sizeof(struct semaphore*));
  sem_broadcast(sem);
  return 0;
}
