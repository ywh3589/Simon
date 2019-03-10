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

  sem_init(&(mailbox->consumer), 1);
  sem_wait(&(mailbox->consumer));

  while (msg_cnt--)
  {
    sem_wait(&(mailbox->fill));
    sleep(3);

    uacquire(&(mailbox->lock));

    mailbox->cnt--;

    urelease(&(mailbox->lock));

    printf(1, "Consumer: I read a message. There are %d messages now.\n", mailbox->cnt);

    sem_signal(&(mailbox->avail));

  }

  sem_signal(&(mailbox->consumer));

  printf(1, "Consumer: Closing...\n");

  shm_close(1);

  exit();
  
  return 0;
}
