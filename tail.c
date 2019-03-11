#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BUFFER_SIZE 2048

int
main(int argc, char *argv[])
{
  char fileName[256];
  char fileBuffer[BUFFER_SIZE];

  if(argc < 2) {
      printf(2, "Usage: tail filename \n");
      exit();
  }
  else {
    int fd;
    int follow = 0;

    strcpy(fileName, argv[1]);

    if (!strcmp("-f", argv[2])) {
        follow = 1;
    }

    fd = open(fileName, O_RDONLY);

    if(fd < 0) {
        printf(1, "error: opening file failed\n");
        exit();
    }

     int oldStart = 0;
     int oldEnd = 0;

    do
    {
      lseek(fd, 0, 0);

      int n = read(fd, fileBuffer, BUFFER_SIZE);

      if (n < 0) {
          printf(1, "error: reading file failed\n");
          close(fd);
          exit();
      }

      int i;

      int start = 0;
      int newLines = 10;

      for (i = n; i > 0; i--) {
          if (fileBuffer[i] == '\n') {
              if (!newLines--) {
                  start = i;
              }
          }
      }

      if (oldStart && oldStart < start) {
          start = oldEnd;
      }

      for (i = start; i < n; i++) {
          if (fileBuffer[i]) {
              printf(1, "%c", fileBuffer[i]);
          }
      }

      oldStart = start;
      oldEnd = n;

      sleep(1);
    } while (follow);

    close(fd);
  }

  exit();
} 