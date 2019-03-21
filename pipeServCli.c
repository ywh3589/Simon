#include "types.h"
#include "stat.h"
#include "user.h"

#define BUFSIZE 256


int main(void)
{
     int childpid;
     int pipes1[2], pipes2[2], length;
     char read_buffer[BUFSIZE], write_buffer[BUFSIZE], answer_buffer[BUFSIZE];


     if(pipe(pipes1) == -1 || pipe(pipes2) == -1){
        printf(1, "ERROR: pipe failed");
        exit();
     }

 if((childpid = fork()) == -1)
        {
                printf(1, "fork error\n");
                exit();
        }
//children
        if(childpid == 0)
        {
                close(pipes1[0]);
                close(pipes2[1]);

                strcpy(write_buffer, "Hi server!\n");
                write(pipes1[1], write_buffer, strlen(write_buffer));
              //  sleep(10);

        if((length= read(pipes2[0], read_buffer, BUFSIZE)) == -1){
                printf(1, "read failed\n");
                exit();
        }

        printf(1, "Ummm... Let me think...\n");
        
        printf(1, "Can you get to know faster?, if you know the answer, type in the aswer!\n");
        gets(answer_buffer, sizeof(answer_buffer));


        sleep(500);


        
        printf(1, "receive message from server : %s \n", read_buffer);
        }
        else
        {
                close(pipes1[1]);
        close(pipes2[0]);

        if((length = read(pipes1[0], read_buffer, BUFSIZE)) == -1){
            printf(1, "ERROR: read failed");
            exit();
        }

        sleep(100);
        printf(1, "receive message from client : %s\n", read_buffer);
     
        strcpy(write_buffer, "Hello client!\n");

        write(pipes2[1], write_buffer, strlen(write_buffer));

        wait();
        }
        exit();


   
     exit();
}
