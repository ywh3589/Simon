#include "types.h"
#include "stat.h"
#include "user.h"
#include "uspinlock.h"
#include "semaphore.h"

struct mailbox {
  struct uspinlock lock;
  semaphore fill;
  semaphore avail;
  semaphore consumer;
  int cnt;
};

int main(int argc, char *argv[])
{
  struct mailbox *mailbox;
  int msg_cnt = 6;

  shm_open(1,(char **)&mailbox);

  sem_init(&(mailbox->fill), 0);
  sem_init(&(mailbox->avail), 3);

  while (msg_cnt--)
  {
    sem_wait(&(mailbox->avail));
    sleep(2);

    uacquire(&(mailbox->lock));

    mailbox->cnt++;

    urelease(&(mailbox->lock));

    printf(1, "Producer: There are %d messages now.\n", mailbox->cnt);

    sem_signal(&(mailbox->fill));

  }

  sem_wait(&(mailbox->consumer));

  printf(1, "Producer: Closing...\n");

  shm_close(1);

  exit();
  
  return 0;
}